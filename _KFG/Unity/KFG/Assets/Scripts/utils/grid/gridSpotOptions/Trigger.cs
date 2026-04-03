using UnityEngine;
using UnityEngine.Events;

namespace utils.grid.gridSpotOptions
{
    [DisallowMultipleComponent]
    public class Trigger : GridSpot.SpotOption
    {
        public UnityEvent<GridSpot> onTrigger = new ();
        
        public virtual void RunTrigger()
        {
            onTrigger?.Invoke(Spot);
        }

        protected override void OnResetOption(){}
    }
}