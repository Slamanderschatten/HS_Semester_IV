using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

namespace utils.pattern.mode
{
    public class ModeMain : MonoBehaviour
    {
        public string modeName;
        public InputActionAsset inputActions;
        public bool frameDelayedModeChange;

        private readonly List<ModeBase> modeInstances = new();
        [SerializeField, ReadOnly]
        private int mode;
        public int LastMode {get; private set;}
        private readonly LinkedList<int> nextModes = new();
        private Coroutine modeChangeRoutine;
        public string ModeName => modeName;


        protected virtual void Awake()
        {
            ModeBase[] modeComponents = GetComponents<ModeBase>();
            foreach (ModeBase comp in modeComponents)
            {
                while(modeInstances.Count <= comp.GetMode())
                    modeInstances.Add(null);
                modeInstances[comp.GetMode()] = comp;
                InitModeComponent(comp);
            }
            if(modeInstances[0] == null)
            {
                //set placeholder for no mode
                modeInstances[0] = gameObject.AddComponent<ModeBase.NoMode>();
                InitModeComponent(modeInstances[0]);
            }
        }
        
        
        protected virtual void InitModeComponent(ModeBase m)
        {
            m.enabled = false;
            m.SetMain(this);
        }
        
        
        public virtual int Mode
        {
            get => mode;
            set
            {
                if(modeInstances[value] == null)
                {
                    Debug.LogError("Component for mode '" + value + "' not exist");
                    return;
                }
                if(frameDelayedModeChange)
                {
                    nextModes.AddLast(value);
                    modeChangeRoutine ??= StartCoroutine(SetModeNextFrame(nextModes.First.Value));
                }
                else
                    SetMode(value);
                    
            }
        }
        public virtual ModeBase ActiveModeComp => modeInstances[Mode];
        
        private void SetMode(int nextMode)
        {
            LastMode = mode;
            ModeBase modeNext = modeInstances[nextMode];
            ModeBase modeBefore = modeInstances[mode];
            if (modeBefore)
                modeBefore.enabled = false;
            modeNext.enabled = true;
            mode = nextMode;
        }
        private IEnumerator SetModeNextFrame(int nextMode)
        {
            if(nextMode != mode)
            {
                yield return null;
                SetMode(nextMode);
            }
            nextModes.RemoveFirst();

            modeChangeRoutine = nextModes.Count > 0
                ? StartCoroutine(SetModeNextFrame(nextModes.First.Value))
                : null;
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        public abstract class ModeBase : MonoBehaviour
        {
            protected ModeMain main;
            protected InputActionMap inputMap;
            public GameObject modeRootObject;
            
            protected virtual void Awake()
            {
                modeRootObject?.SetActive(false);
                AwakeModeRootObj();
            }
            protected abstract void AwakeModeRootObj();

            protected void OnDestroy()
            {
                UnsubscribeInputEvents();
            }

            public virtual void SetMain(ModeMain mainComponent)
            {
                if(inputMap != null)
                    UnsubscribeInputEvents();
                main = mainComponent;
                if(main)
                {
                    inputMap = main.inputActions.FindActionMap(main.ModeName + GetModeName());
                    if(inputMap != null)
                    {
                        inputMap.Disable();
                        SubscribeInputEvents();
                    }
                    InitMain();
                }
            }
            protected abstract void InitMain();

            public abstract int GetMode();
            public abstract string GetModeName();
            public virtual void SetMode() => main.Mode = GetMode();

            protected virtual void OnEnable()
            {
                if(modeRootObject != null)
                {
                    modeRootObject.SetActive(true);
                    FUtils.SelectFirstSelectableObject(modeRootObject);
                }
                inputMap?.Enable();
                OnEnableMode();
            }

            protected abstract void OnEnableMode();
            protected virtual void OnDisable()
            {
                if(modeRootObject != null)
                    modeRootObject.SetActive(false);
                inputMap?.Disable();
                OnDisableMode();
            }
            protected abstract void OnDisableMode();
            protected abstract void SubscribeInputEvents();
            protected abstract void UnsubscribeInputEvents();
            
            
            
            
            
            
            
            public class NoMode : ModeBase
            {
                protected override void AwakeModeRootObj(){}
                protected override void InitMain(){}
                public override int GetMode() => 0;
                public override string GetModeName() => "No";

                protected override void OnEnableMode(){}
                protected override void OnDisableMode(){}
                protected override void SubscribeInputEvents(){}

                protected override void UnsubscribeInputEvents(){}
            }
            
        }
    }
}