using UnityEngine;

namespace npc.options
{
    public class TextOutput : NpcOption
    {
        
        protected override void OnResetOption()
        {
        }

        protected override void OnActivation()
        {
            Debug.Log("Hallo");
        }

        protected override void OnDeactivation()
        {
            Debug.Log("By");
        }

        protected override void OnPause()
        {
        }

        protected override void OnResume()
        {
        }
    }
}