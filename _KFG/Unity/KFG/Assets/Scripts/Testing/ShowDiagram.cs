using System;
using System.Collections.Generic;
using System.Linq;
using Ground;
using UnityEngine;

namespace Testing
{
    public class ShowDiagram : MonoBehaviour

    {
        public int valueNumber;

        private readonly List<int> values = new();
        private List<Transform> chartBars;

        private void Awake()
        {
            chartBars = GetComponentsInChildren<Transform>().ToList();
            chartBars.Remove(transform);
        }

        [ContextMenu("Gleichverteilter Random wert")]
        public void Random()
        {
            values.Clear();
            while(values.Count < chartBars.Count)
                values.Add(0);
            for(int i = 0; i < valueNumber; i++)
                values[UnityEngine.Random.Range(0, chartBars.Count)]++;
            ShowBars();
        }
        
        [ContextMenu("Normalverteilter Random wert")]
        public void RandomNormal()
        {
            values.Clear();
            while(values.Count < chartBars.Count)
                values.Add(0);
            for(int i = 0; i < valueNumber; i++)
                values[RandomCharacterSpawner.RandomRangeNormal(0, chartBars.Count)]++;
            ShowBars();
        }


        private void ShowBars()
        {
            for (int i = 0; i < chartBars.Count; i++)
                chartBars[i].transform.localScale = new Vector3(0, values[i], 0);
        }
    }
}