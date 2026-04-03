using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.Events;

namespace utils.grid.gridSpotOptions
{
    [DisallowMultipleComponent]
    public class Focusable : GridSpot.SpotOption
    {
        
        public UnityEvent<GridSpot> onFocus;
        public UnityEvent<GridSpot> onUnFocus;
        
        public bool Focused {get; private set;}


        protected override void OnEnable()
        {
            base.OnEnable();
            optMgmt.Holder.Grid?.AddSpot(Spot);
        }


        protected override void OnDisable()
        {
            base.OnDisable();
            optMgmt.Holder.Grid?.RemoveSpot(Spot);
        }


        public virtual void Focus()
        {
            if(Focused)
                return;
            Focused = true;
            onFocus?.Invoke(Spot);
        }
        public virtual void UnFocus()
        {
            if(!Focused)
                return;
            Focused = false;
            onUnFocus?.Invoke(Spot);
        }

        protected override void OnResetOption()
        {
            UnFocus();
        }
    }
}