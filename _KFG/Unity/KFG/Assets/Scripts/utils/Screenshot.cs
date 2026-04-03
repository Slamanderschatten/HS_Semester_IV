using System.IO;
using UnityEngine;
using UnityEngine.UI;

namespace utils
{
    public class Screenshot : MonoBehaviour
    {
        public Camera screenshotCam;
        public GameObject[] maskObjects;
        
        
        private void Awake()
        {
            foreach (GameObject o in maskObjects)
                o?.SetActive(false);
        }

        /// <summary>
        /// Macht einen Screenshot von der Kamera, zeigt ihn in der UI und speichert ihn
        /// </summary>
        /// <param name="filename">z.B. "Save1.png"</param>
        /// <param name="height">Auflösung Höhe</param>
        /// <param name="width">Auflösung Breite</param>
        public Texture2D TakeScreenshot(int height, int width)
        {
            if (screenshotCam == null)
            {
                Debug.LogError("ScreenshotCam nicht gesetzt!");
                return null;
            }

            // RenderTexture mit Alpha
            RenderTexture rt = new RenderTexture(width, height, 24, RenderTextureFormat.ARGB32);
            rt.antiAliasing = 4;
            screenshotCam.targetTexture = rt;

            // Kamera aktivieren, MaskPlanes aktivieren
            screenshotCam.gameObject.SetActive(true);
            foreach (GameObject o in maskObjects)
                o?.SetActive(true);

            // Screenshot aufnehmen
            Texture2D tex = new Texture2D(width, height, TextureFormat.RGBA32, false);
            screenshotCam.Render();
            RenderTexture.active = rt;
            tex.ReadPixels(new Rect(0, 0, width, height), 0, 0);
            tex.Apply();

            // Aufräumen
            screenshotCam.gameObject.SetActive(false);
            foreach (GameObject o in maskObjects)
                o?.SetActive(false);
            screenshotCam.targetTexture = null;
            RenderTexture.active = null;
            
            Destroy(rt);
            
            return tex;
        }
        
        
        
        
        
        
        
        
        
        
        
    }
}