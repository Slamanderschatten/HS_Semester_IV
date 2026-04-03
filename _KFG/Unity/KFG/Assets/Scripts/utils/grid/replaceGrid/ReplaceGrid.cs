using UnityEditor.VersionControl;
using UnityEngine;
using utils.grid.gridSpotOptions;

namespace utils.grid.replaceGrid
{
    public class ReplaceGrid : SelectionGrid
    {
        public delegate void ReplaceModeChangeHandle(ReplaceMode modeBefore, ReplaceMode modeNow);
        public delegate void PlacesSwitchedHandle(Place selected, Place focused);
        public event ReplaceModeChangeHandle OnChangeMode;
        public event PlacesSwitchedHandle OnSwitch;
        public event PlacesSwitchedHandle OnCancel;

        private ReplaceMode attr_mode;
        public ReplaceMode Mode
        {
            get => attr_mode;
            private set
            {
                if(attr_mode != value)
                {
                    ReplaceMode old = attr_mode;
                    attr_mode = value;
                    OnChangeMode?.Invoke(old, value);
                }
            }
        }

        private bool attr_selectButtonPressed;

        public bool SelectButtonPressed
        {
            get => attr_selectButtonPressed;
            set
            {
                if(attr_selectButtonPressed != value)
                {
                    attr_selectButtonPressed = value;
                    if(!value)
                        Selection();
                }
            }
        }
        
        public Place FocusedPlace => FocusedSpot?.Get<Place>();
        public IReplaceable FocusedReplaceable => FocusedPlace?.PlacedReplaceable;
        public Place SelectedPlace => SelectedSpot?.Get<Place>();
        public IReplaceable SelectedReplaceable => SelectedPlace?.PlacedReplaceable;
        
        
        

        public override void Enable()
        {
            base.Enable();
            if(SelectButtonPressed)
                Mode = ReplaceMode.IgnoreNextSelection;
        }
        public override void Disable()
        {
            base.Disable();
        }


        protected void Selection()
        {
            if(!Enabled)
                return;
            
            if(Mode == ReplaceMode.IgnoreNextSelection)
            {
                Mode = ReplaceMode.None;
                return;
            }
            
            if(FocusedPlace != null)
            {
                TriggerFocused();
                switch (Mode)
                {
                    case ReplaceMode.None:
                        Select();
                        break;
                    case ReplaceMode.EmptyPlaceSelected:
                        if (FocusedPlace.PlacedReplaceable != null)
                            SwitchSelectedWithFocused();
                        break;
                    case ReplaceMode.OccupiedPlaceSelected:
                        SwitchSelectedWithFocused();
                        break;
                    case ReplaceMode.Dragged:
                        Drop();
                        break;
                }
            }
            else
            {
                Cancel();
                base.Select();
            }
        }
        
        
        public override GridSpot GoToNearest(Vector2 position)
        {
            if(!Enabled)
                return null;
            IReplaceable replaceable = FocusedReplaceable;
            GridSpot nearest = base.GoToNearest(position, out bool switched);
            if(SelectButtonPressed && switched)
                Drag(replaceable);
            return nearest;
        }
        
        
        public override GridSpot GoToDirection(Vector2 direction)
        {
            if(!Enabled)
                return null;
            if(SelectButtonPressed)
                Drag(FocusedReplaceable);
            return base.GoToDirection(direction);
        }


        public override void UnFocus()
        {
            if(SelectButtonPressed)
                Drag(FocusedReplaceable);
            base.UnFocus();
        }


        /********************************** SWITCH *********************************************/
        
        
        private bool SwitchSelectedWithFocused()
        {
            if(FocusedPlace != null && 
               FocusedPlace.GetOtherOption<Selectable>() != null && 
               SelectedPlace != null)
            {
                if(SelectedPlace.SwitchIfPossible(FocusedPlace))
                {
                    Mode = ReplaceMode.None;
                    OnSwitch?.Invoke(FocusedPlace, SelectedPlace);
                    
                    Deselect();
                    return true;
                }
            }
            
            Cancel();
            return false;
        }
        
        
        public virtual void Cancel()
        {
            OnCancel?.Invoke(SelectedPlace, FocusedPlace);
            SelectedPlace?.ResetPlaced();
            FocusedPlace?.ResetPlaced();
            Deselect();
            Mode = SelectButtonPressed ? ReplaceMode.IgnoreNextSelection : ReplaceMode.None;
        }
        
        
        public override void Reset()
        {
            Cancel();
            base.Reset();
        }




        /********************************** SELECT *********************************************/


        public override bool Select()
        {
            if(base.Select())
            {
                if(SelectedReplaceable == null)
                    Mode = ReplaceMode.EmptyPlaceSelected;
                else 
                    Mode = ReplaceMode.OccupiedPlaceSelected;
                return true;
            }
            return false; 
        }



        /********************************** DRAG AND DROP *********************************************/
        
        
        private void Drag(IReplaceable replaceable)
        {
            if(Mode != ReplaceMode.None)
                return;

            Mode = replaceable != null && Select(replaceable.Spot) ? ReplaceMode.Dragged : ReplaceMode.IgnoreNextSelection;
        }
        
        
        private void Drop()
        {
            if(Mode != ReplaceMode.Dragged)
                return;
            SwitchSelectedWithFocused();
        }
        
        
        
        
        
        
        
        
        
        
        
        

        public enum ReplaceMode
        {
            None = 0,
            EmptyPlaceSelected = 1,
            OccupiedPlaceSelected = 2,
            Dragged = 3,
            IgnoreNextSelection = 4,
        }
        
        
        
        
    }
}