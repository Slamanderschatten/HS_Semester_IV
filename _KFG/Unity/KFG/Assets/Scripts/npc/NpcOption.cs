using System;
using System.Collections;
using UnityEngine;
using utils.pattern.option;

namespace npc
{
    public abstract class NpcOption : Option<NPC, NpcOption>
    {
        [SerializeField] private float maxDuration;
        [SerializeField] private float cooldownTime;


        private float maxDurationEnd;
        private Coroutine maxDurationCoroutine;
        private float cooldownTimeEnd;
        
        
        public virtual bool Active { get; private set; }
        public virtual bool Paused { get; private set; }
            
        public virtual void Activate()
        {
            if (Active || Time.time < cooldownTimeEnd)
                return;
            Active = true;
            if(maxDuration > 0)
            {
                maxDurationEnd = Time.time + maxDuration;
                maxDurationCoroutine = StartCoroutine(DeactivateAfterDuration());
            }
            OnActivation();
        }
        protected abstract void OnActivation();


        protected virtual IEnumerator DeactivateAfterDuration()
        {
            while (Time.time < maxDurationEnd)
                yield return new WaitForSeconds(maxDurationEnd - Time.time);
            maxDurationCoroutine = null;
            Deactivate();
        }


        public virtual void Deactivate()
        {
            if(maxDurationCoroutine != null)
            {
                StopCoroutine(maxDurationCoroutine);
                maxDurationCoroutine = null;
            }
            if (!Active)
                return;
            Active = false;
            cooldownTimeEnd = Time.time + cooldownTime;
            OnDeactivation();
        }
        protected abstract void OnDeactivation();


        public virtual void Pause()
        {
            if (Paused)
                return;
            Paused = true;
            OnPause();
        }
        protected abstract void OnPause();

        public virtual void Resume()
        {
            if (!Paused)
                return;
            Paused = false;
            OnResume();
        }
        protected abstract void OnResume();

    }
}