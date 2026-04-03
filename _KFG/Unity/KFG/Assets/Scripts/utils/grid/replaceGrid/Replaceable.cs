using System;

namespace utils.grid.replaceGrid
{
    public interface IReplaceable
    {
        
        
        public Int64 PlaceFlags {get; set;}
        public bool Selected { get; set; }
        public bool Focused { get; set; }
        
        public GridSpot Spot {get; set; }
    }
}