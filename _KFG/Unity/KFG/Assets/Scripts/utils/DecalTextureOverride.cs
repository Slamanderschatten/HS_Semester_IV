using System;
using UnityEngine;
using UnityEngine.Rendering.Universal;

namespace utils
{
    public class DecalTextureOverride : MonoBehaviour
    {
        public Sprite sprite;
        public Texture2D texture;
        
        
        private void Awake()
        {
            SetTexture();
        }
        
        
        public void SetTexture()
        {
            Texture2D tex = texture;
            if(sprite != null)
                tex = sprite.texture;
            DecalProjector decal = GetComponentInChildren<DecalProjector>();
            if(decal.material == null)
            {
                Debug.LogError("DecalMaterial missing in Object: " + name);
                return;
            }
            Material mat = new(decal.material);
            mat.SetTexture("Base_Map", tex);
            decal.material = mat;
        }
    }
}