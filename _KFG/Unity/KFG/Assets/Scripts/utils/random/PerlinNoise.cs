using System;
using UnityEngine;
using Random = UnityEngine.Random;

namespace utils.random
{
    public class PerlinNoise
    {
        private readonly float[][] values;
        private readonly float min;
        private readonly float max;
        private readonly uint octaves;


        public PerlinNoise(float min, float max, uint octaves)
        {
            if (octaves == 0)
                throw new ArgumentException("octaves can not be zero");
            
            this.min = min;
            this.max = max;
            this.octaves = octaves;
            values  = new float[][octaves];
            for (int i = 0; i < octaves; i++)
                values[i] = new float[i+1];
            NextArea(false);
        }


        public float GetValue(float tDelta)
        {
            switch (tDelta)
            {
                case >= 2:
                    NextArea(false);
                    tDelta %= 2;
                    break;
                case >= 1:
                    NextArea();
                    tDelta -= 1;
                    break;
            }

            return InterpolateValue(tDelta);
        }


        private void NextArea(bool expand = true)
        {
            int startIndex = 0;
            if (expand)
            {
                startIndex = 1;
                for (int i = 0; i < octaves; i++)
                    values[octaves][0] = values[octaves][i+1];
            }
            for (int octave = 0; octave < octaves; octave++)
            {
                for(int i = startIndex; i <= octave; i++)
                    values[octave][i] = RandNormal();
            }   
        }


        private float InterpolateValue(float t)
        {
            int index = (int)(t * octaves);
            t = Mathf.SmoothStep(0f, 1f, t);
            return 0;
        }


        private float RandNormal()
        {
            return (Random.Range(min, max) + Random.Range(min, max)) / 2;
        }
        
        
    }
}