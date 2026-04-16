using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using Ground;
using UnityEngine;

namespace Testing
{
    public class ShowDiagram : MonoBehaviour

    {
        public int valueNumber = 5000;
        public float scaleMultiplier = 1f;

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
            ExportToCsv();
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
            ExportToCsv();
        }


        private void ShowBars()
        {
            for (int i = 0; i < chartBars.Count; i++)
                chartBars[i].transform.localScale = new Vector3(1, values[i] * scaleMultiplier, 1);
        }


        private void ExportToCsv()
        {
            string filePath = Application.dataPath + "/ChartData.csv";
            StringBuilder sb = new StringBuilder();

            // CSV Header (optional)
            sb.AppendLine("BarIndex;Value");

            // Daten hinzufügen
            for (int i = 0; i < values.Count; i++)
            {
                sb.AppendLine($"{i};{values[i]}");
            }

            // Datei schreiben
            File.WriteAllText(filePath, sb.ToString());
            Debug.Log($"Daten erfolgreich exportiert nach: {filePath}");
        }
    }
}