using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace utils.pattern.option
{
    public class OptionMgmt<optionMgmtHolderT, optionT> : IEnumerable<optionT>
        where optionMgmtHolderT : Component
        where optionT : Option<optionMgmtHolderT, optionT>
    {
        public optionMgmtHolderT Holder {get;}
        public optionT FirstOption {get; private set;}
        
        
        
        
        public OptionMgmt(optionMgmtHolderT holder)
        {
            Holder = holder;
            
            optionT[] options = Holder.GetComponents<optionT>();
            foreach (optionT option in options)
                option.SetBase(this);
            FirstOption?.BaseInitialized();
        }
        
        
        protected bool ReplaceOption(optionT optionToReplace, optionT newOption)
        {
            if(newOption != null && !newOption.enabled)
                return false;
            if(FirstOption == newOption)
                return false;
            if(FirstOption == optionToReplace)
            {
                FirstOption = newOption;
                return true;
            }
            return FirstOption?.ReplaceOptionInternal(optionToReplace, newOption) ?? false;
        }
        
        
        internal bool OptionSelfActivation(optionT optionToEnable)
            => ReplaceOption(null, optionToEnable);
        
        
        internal bool OptionSelfDeactivation(optionT optionToDisable)
            => ReplaceOption(optionToDisable, optionToDisable.NextOption);
        
        
        public bool ActivateOption<specificOptionT>()
            where specificOptionT : optionT
        {
            if(IsActive<specificOptionT>())
                return false;
            optionT option = Holder.GetComponent<specificOptionT>();
            if(option != null)
            {
                OptionSelfActivation(option);
                return true;
            }
            return false;
        }
        
        
        public specificOptionT Get<specificOptionT>() where specificOptionT : optionT
            => FirstOption?.GetOptionInternal<specificOptionT>();
        public bool IsActive<specificOptionT>() where specificOptionT : optionT
            => FirstOption?.HasOptionInternal<specificOptionT>() ?? false;
        public bool Exists<specificOptionT>() where specificOptionT : optionT
            => Holder.GetComponent<specificOptionT>() != null;
        public void ResetOptions()
            => FirstOption?.ResetOption();
        
        
        


        public IEnumerator<optionT> GetEnumerator()
        {
            optionT option = FirstOption;
            while(option != null)
            {
                yield return option;
                option = option.NextOption;
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
        
        
        
        
        
        
        
    }
}