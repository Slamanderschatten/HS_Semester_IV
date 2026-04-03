using UnityEngine;
using UnityEngine.Events;

namespace utils.grid.gridSpotOptions
{
    [DisallowMultipleComponent]
    public class Selectable : GridSpot.SpotOption
    {
        
        public UnityEvent<GridSpot> onSelect;
        public UnityEvent<GridSpot> onUnSelect;
        
        public bool Selected {get; private set;}
        
        public virtual void Select() 
        {
            if(Selected)
                return;
            Selected = true;
            onSelect?.Invoke(Spot);
            
        }
        public virtual void UnSelect()
        {
            if(!Selected)
                return;
            Selected = false;
            onUnSelect?.Invoke(Spot);
        }

        protected override void OnResetOption()
        {
            UnSelect();
        }
    }
}