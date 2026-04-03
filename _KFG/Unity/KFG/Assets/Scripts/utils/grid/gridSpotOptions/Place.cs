using System;
using UnityEngine;
using utils.grid.replaceGrid;

namespace utils.grid.gridSpotOptions
{
    [DisallowMultipleComponent]
    public class Place : GridSpot.SpotOption
    {
        [Header("Placeable Components: Type masks")]
        public virtual Int64 ExactTheseFlags {get; set;}
        public virtual Int64 NoneOfTheseFlags {get; set;}
        public virtual Int64 MinOneOfTheseFlags {get; set;} = Int64.MaxValue;
        public virtual Int64 AllOfTheseFlags {get; set;}
        
        
        
        public IReplaceable PlacedReplaceable {get; private set;}


        protected override void OnBaseInitialized()
        {
            base.OnInitBase();
            Focusable focusable = optMgmt.Get<Focusable>();
            if (focusable != null)
            {
                focusable.onFocus.AddListener(FocusPlaced);
                focusable.onUnFocus.AddListener(UnFocusPlaced);
            }
            Selectable selectable = optMgmt.Get<Selectable>();
            if (selectable != null)
            {
                selectable.onSelect.AddListener(SelectPlaced);
                selectable.onUnSelect.AddListener(UnSelectPlaced);
            }
        }


        protected override void OnResetOption()
        {
        }
        
        
        public virtual void ResetPlaced()
        {
            ActualizePlaced();
        }
        
        
        protected virtual void FocusPlaced(GridSpot spot)
        {
            if(PlacedReplaceable != null)
                PlacedReplaceable.Focused = true;
        }
        protected virtual void UnFocusPlaced(GridSpot spot)
        {
            if(PlacedReplaceable != null)
                PlacedReplaceable.Focused = false;
        }
        protected virtual void SelectPlaced(GridSpot spot)
        {
            if(PlacedReplaceable != null)
                PlacedReplaceable.Selected = true;
        }
        protected virtual void UnSelectPlaced(GridSpot spot)
        {
            if(PlacedReplaceable != null)
                PlacedReplaceable.Selected = false;
        }
            
        
        
        

        
        public virtual bool PlaceFlagsPossible(long flags)
        {
            
            if (ExactTheseFlags != 0)
                return flags == ExactTheseFlags;
            if ((flags & NoneOfTheseFlags) == 0 &&
                (flags & MinOneOfTheseFlags) != 0 &&
                (flags & AllOfTheseFlags) == AllOfTheseFlags)
                return true;
            return false;
        }
        

        public virtual bool PlacementPossible(IReplaceable replaceable)
        {
            if(replaceable == null)
                return true;
            return PlaceFlagsPossible(replaceable.PlaceFlags);
        }
        
        
        public virtual bool PlaceIfPossible(IReplaceable replaceable)
        {
            if(!Empty() || !PlacementPossible(replaceable))
                return false;
            
            PlaceForced(replaceable);
            return true;
        }
        
        
        public virtual bool SwitchIfPossible(ref IReplaceable replaceable)
        {
            if(!PlacementPossible(replaceable))
                return false;
            
            IReplaceable oldReplaceable = PlacedReplaceable;
            PlaceForced(replaceable);
            replaceable = oldReplaceable;
            return true;
        }
        
        
        public virtual bool SwitchIfPossible(Place other)
        {
            if(other == null || !PlacementPossible(other.PlacedReplaceable))
                return false;
            
            IReplaceable replaceable = PlacedReplaceable;
            if(other.SwitchIfPossible(ref replaceable))
            {
                PlaceForced(replaceable);
                return true;
            }
            return false;
        }
        
        
        public virtual IReplaceable PlaceForced(IReplaceable replaceable)
        {
            IReplaceable old = Remove();
            replaceable?.Spot?.Get<Place>()?.Remove();
            PlacedReplaceable = replaceable;
            if(PlacedReplaceable == null)
                return null;
            
            PlacedReplaceable.Spot = Spot;
            ActualizePlaced();
            return old;
        }
        
        
        protected virtual void ActualizePlaced()
        {
            if(PlacedReplaceable == null)
                return;
            
            PlacedReplaceable.Selected = optMgmt?.Get<Selectable>()?.Selected ?? false;
            PlacedReplaceable.Focused = optMgmt?.Get<Focusable>()?.Focused ?? false;
            ActualizePlacedReplaceable();
        }
        protected virtual void ActualizePlacedReplaceable() {} //Event
        
        
        public virtual IReplaceable Remove()
        {
            if(PlacedReplaceable == null || PlacedReplaceable.Spot != Spot)
                return null;
            
            PlacedReplaceable.Selected = false;
            PlacedReplaceable.Focused = false;
            PlacedReplaceable.Spot = null;
            IReplaceable replaceable = PlacedReplaceable;
            PlacedReplaceable = null;
            return replaceable;
        }
        
        
        public virtual bool Empty() => PlacedReplaceable == null;
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    }
}