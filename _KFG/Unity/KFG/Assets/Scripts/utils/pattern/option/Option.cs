using UnityEngine;

namespace utils.pattern.option
{
    public abstract class Option<optionMgmtHolderT, optionT> : MonoBehaviour
        where optionMgmtHolderT : Component
        where optionT : Option<optionMgmtHolderT, optionT>
    {
        protected OptionMgmt<optionMgmtHolderT, optionT> optMgmt;
        public optionMgmtHolderT Holder => optMgmt.Holder;
        protected optionT nextOption;
        public optionT NextOption => nextOption;


        protected virtual void OnEnable()
        {
            optMgmt?.OptionSelfActivation(this as optionT);
        }
        
        
        protected virtual void OnDisable()
        {
            ResetOption();
            optMgmt?.OptionSelfDeactivation(this as optionT);
            nextOption = null;
        }


        internal bool ReplaceOptionInternal(optionT optionToReplace, optionT newOption)
        {
            if(nextOption == newOption)
                return false;
            if(nextOption == optionToReplace)
            {
                nextOption = newOption;
                return true;
            }
            return nextOption?.ReplaceOptionInternal(optionToReplace, newOption) ?? false;
        }
        
        
        public void SetBase(OptionMgmt<optionMgmtHolderT, optionT> optionMgmt)
        {
            if(optMgmt != null)
            {
                optMgmt.OptionSelfDeactivation(this as optionT);
                OnRemoveBase();
            }
            optMgmt = optionMgmt;
            if(optMgmt != null)
            {
                OnInitBase();
                if(enabled)
                    optMgmt.OptionSelfActivation(this as optionT);
            }
        }
        protected virtual void OnRemoveBase(){}
        protected virtual void OnInitBase(){}
        public virtual void BaseInitialized()
        {
            OnBaseInitialized();
            nextOption?.BaseInitialized();
        }
        protected virtual void OnBaseInitialized(){}
        
        
        internal specificOptionT GetOptionInternal<specificOptionT>() where specificOptionT : optionT
        {
            if(this is specificOptionT)
                return this as specificOptionT;
            return nextOption?.GetOptionInternal<specificOptionT>();
        }
        public optionT GetOtherOption<specificOptionT>() where specificOptionT : optionT 
            => optMgmt.Get<specificOptionT>();
        
        
        internal bool HasOptionInternal<specificOptionT>() where specificOptionT : optionT
        {
            if(this is specificOptionT)
                return true;
            return nextOption?.HasOptionInternal<specificOptionT>() ?? false;
        }
        public bool HasOtherOption<specificOptionT>() where specificOptionT : optionT
            => optMgmt.IsActive<specificOptionT>();
        
        
        public void ResetOption()
        {
            OnResetOption();
            nextOption?.ResetOption();
        }
        protected abstract void OnResetOption();
        
    }
}