using UnityEngine;

namespace utils
{
    public class TextureOverride : MonoBehaviour
    {
        public Texture2D texture;
        
        private void Awake()
        {
            Renderer rend = GetComponent<Renderer>();
            if(rend == null)
                return;
            if(rend.material == null)
            {
                Debug.LogWarning("Material missing in Object: " + name);
                return;
            }
            rend.material.mainTexture = texture;
        }
        
    }
}