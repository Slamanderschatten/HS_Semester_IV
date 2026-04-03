

using System;
using UnityEngine;
using utils.grid.gridSpotOptions;
using utils.pattern.option;

namespace utils.grid
{
    [DisallowMultipleComponent]
    public abstract class GridSpot : MonoBehaviour
    {
        
        [ReadOnly]
        public int id;
        public OptionMgmt<GridSpot, SpotOption> Options {get; private set;}
        public SelectionGrid Grid {get; set;}
        public abstract Vector2 Pos { get; }


        protected virtual void Awake()
        {
            Options = new(this);
        }
        
        
        public t Get<t>() where t : SpotOption
            => Options.Get<t>();
        public bool Is<t>() where t : SpotOption
            => Options.IsActive<t>();
        public virtual void ResetOptions()
            => Options.ResetOptions();
        
        
        
        public static Vector2 ProjectToPlane(Vector3 v, Vector3 normal)
        {
            Vector3 projected = Vector3.ProjectOnPlane(v, normal);
            return new Vector2(projected.x, projected.z);
        }
        
        
        
        
        
        
        
        
        
        public abstract class SpotOption : Option<GridSpot, SpotOption>
        {
            public GridSpot Spot {get; private set;}
            
            protected override void OnInitBase()
            {
                Spot = optMgmt?.Holder.GetComponent<GridSpot>();
            }
            protected override void OnRemoveBase()
            {
                Spot = null;
            }
        }
        
        
    }
}