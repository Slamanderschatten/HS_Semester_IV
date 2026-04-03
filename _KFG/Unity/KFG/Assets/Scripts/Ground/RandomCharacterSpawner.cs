using System.Collections.Generic;
using npc;
using UnityEngine;

namespace Ground
{
    public class RandomCharacterSpawner : MonoBehaviour
    {
        

        public GameObject ground;
        public GameObject[] prefabs;
        public int instanceCount;
        public float groundScaleMultiplier;

        private readonly List<NPC> npcs = new();

        void Start()
        {
            Reload();
        }


        void Update()
        {
            if(Input.GetKeyDown(KeyCode.R))
                Reload();
        }

        private void Reload()
        {
            foreach (NPC item in npcs)
            {
                Destroy(item.gameObject);
            }
            float sizeX = ground.transform.localScale.x * groundScaleMultiplier;
            float sizeZ = ground.transform.localScale.z * groundScaleMultiplier;
            if (instanceCount < 1)
                instanceCount = 1;
            for(int i = 0; i < instanceCount; i++)
            {
                int prefabIndex = Random.Range(0, prefabs.Length);
                
                float xPos = Random.Range(0, sizeX);
                float zPos = Random.Range(0, sizeZ);

                GameObject obj = Instantiate(prefabs[prefabIndex], transform);
                obj.transform.localPosition = new Vector3(xPos - sizeX/2, 0, zPos - sizeZ/2);
                obj.transform.localRotation = Quaternion.Euler(0, Random.Range(0, 360), 0);
                obj.transform.localScale = Vector3.one * RandomRangeNormal(0.5f, 1.5f);
                npcs.Add(obj.GetComponent<NPC>());
            }
        }


        public static int RandomRangeNormal(int min, int max)
        {
            return (Random.Range(min, max) + Random.Range(min, max)) / 2;
        }
        public static float RandomRangeNormal(float min, float max)
        {
            return (Random.Range(min, max) + Random.Range(min, max)) / 2;
        }
    }
}