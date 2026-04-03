using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;
using UnityEditor;
using UnityEditor.Rendering;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.InputSystem;
using UnityEngine.UI;

namespace utils
{
    public static class FUtils
    {
        
        public static Transform FindChildByNameRecursive(Transform parent, string objectName)
        {
            foreach (Transform child in parent)
            {
                if (child.name == objectName)
                    return child;
                var result = FindChildByNameRecursive(child, objectName);
                if (result != null)
                    return result;
            }
            return null;
        }
        

        public static bool GetMouseHit(out Vector3 hitPos, LayerMask layerMask)
        {
            Vector2 mousePos = Mouse.current.position.ReadValue();
            Ray ray = Camera.main.ScreenPointToRay(mousePos);

            if (Physics.Raycast(ray, out RaycastHit hit, Mathf.Infinity, layerMask))
            {
                hitPos = hit.point;
                return true;
            }
            hitPos = Vector3.negativeInfinity;
            return false;
        }
        

        public static RaycastHit[] GetMouseHits(LayerMask layerMask)
        {
            Vector2 mousePos = Mouse.current.position.ReadValue();
            Ray ray = Camera.main.ScreenPointToRay(mousePos);
            return Physics.RaycastAll(ray, Mathf.Infinity, layerMask);
        }
        public static bool GetMouseHits(out RaycastHit[] hits, LayerMask layerMask)
        {
            hits = GetMouseHits(layerMask);
            return hits.Length > 0;
        }
        
        
        public static bool SegmentsCross(Vector2 start1, Vector2 end1, Vector2 start2, Vector2 end2)
        {
            Vector2 p = new(start1.x, start1.y);
            Vector2 r = new(end1.x - start1.x, end1.y - start1.y);
            Vector2 q = new(start2.x, start2.y);
            Vector2 s = new(end2.x - start2.x, end2.y - start2.y);

            float rxs = r.x * s.y - r.y * s.x;

            // Kollinear oder parallel → kein echter Schnitt
            if (Mathf.Approximately(rxs, 0f))
                return false;

            float t = ((q.x - p.x) * s.y - (q.y - p.y) * s.x) / rxs;
            float u = ((q.x - p.x) * r.y - (q.y - p.y) * r.x) / rxs;

            // Echter Schnitt nur, wenn beide im offenen Intervall (0,1) liegen
            return t > 0f && t < 1f && u > 0f && u < 1f;
        }
        
        
        public static bool Intersection(Vector2 start1, Vector2 end1, Vector2 start2, Vector2 end2, 
            out Vector2 intersection)
        {
            if(SegmentsCross(start1, end1, start2, end2))
            {
                // Nur XZ-Werte verwenden

                Vector2 d1 = end1 - start1;
                Vector2 d2 = end2 - start2;
                Vector2 r = start1 - start2;

                float a = Vector2.Dot(d1, d1);
                float b = Vector2.Dot(d1, d2);
                float c = Vector2.Dot(d2, d2);
                float d = Vector2.Dot(d1, r);
                float e = Vector2.Dot(d2, r);

                float denominator = a * c - b * b;

                float t = (b * e - c * d) / denominator;

                intersection = start1 + d1 * t;
                
                return true;
            }
            intersection = Vector3.negativeInfinity;
            return false;
        }
        
        
        public static bool IntersectionProjectedDown(Vector3 start1, Vector3 end1, Vector3 start2, Vector3 end2, 
            out Vector3 intersection)
        {
            bool ret = Intersection(
                new Vector2(start1.x, start1.z),
                new Vector2(end1.x, end1.z),
                new Vector2(start2.x, start2.z),
                new Vector2(end2.x, end2.z),
                out Vector2 intersection2D);
            intersection = new Vector3(intersection2D.x, 0, intersection2D.y);
            return ret;
        }
        
        
        public static void DrawGizmosArrow(Vector3 start, Vector3 directionLenght, Color color)
        {
            
            Gizmos.color = color;
            Vector3 end = start + directionLenght;

            Gizmos.DrawLine(start, end);

            Vector3 right = Quaternion.LookRotation(directionLenght) * Quaternion.Euler(0, 150, 0) * Vector3.forward;
            Vector3 left  = Quaternion.LookRotation(directionLenght) * Quaternion.Euler(0, -150, 0) * Vector3.forward;

            float length = directionLenght.magnitude / 5;
            Gizmos.DrawLine(end, end + right * length);
            Gizmos.DrawLine(end, end + left * length);
        }
        
        
        public static void SelectFirstSelectableObject(GameObject obj)
        {
            Selectable firstSelectable = obj.GetComponentInChildren<Selectable>();
            if(firstSelectable == null)
                return;
            EventSystem.current.SetSelectedGameObject(firstSelectable.gameObject);
        }
        
        
        public static string EncryptInt(int value)
        {
            return value.ToString();
            //todo
            /*const char letterOffcet = (char)('A' - '0');
            string encrypted = "";
            string asString = value.ToString();
            long checksum = 0;
            foreach (char c in asString)
            {
                checksum += c; 
                encrypted += (char)(c + letterOffcet);
            }
            encrypted += "X";
            asString = checksum.ToString();
            foreach (char c in asString)
                encrypted += (char)(c + letterOffcet);
            
            return encrypted;*/
        }
        public static int DecryptInt(string value)
        {
            if(String.IsNullOrEmpty(value))
                return 0;
            return int.Parse(value);
            //todo
            /*if(String.IsNullOrEmpty(value))
                return 0;
            const char letterOffcet = (char)('A' - '0');
            int checksum = 0;
            string asString = "";
            int i = 0;
            for(; i < value.Length && value[i] != 'X'; i++)
            {
                char letter = (char)(value[i] - letterOffcet);
                checksum += letter;
                asString += letter;
            }
            
            if(!int.TryParse(asString, out int decrypted))
                return 0;
            asString = "";
            
            for(i++; i < value.Length; i++)
                asString += (char)(value[i] - letterOffcet);
            if(!int.TryParse(asString, out var storedChecksum) || storedChecksum != checksum)
                return 0;
            
            return decrypted;*/
        }
        
        
        public static string ValidateHex(string value)
        {
            return Regex.Replace(value, @"[^0-9a-fA-F]", "").ToUpper();
        }
        
        
        public static string UpperFirst(string s)
            => string.IsNullOrEmpty(s) ? s : char.ToUpper(s[0]) + s.Substring(1);
        
        
        public static List<searched> GetComponentsInChildren<searched, breakComp>(Transform obj, 
            bool excludeOwnSearched = false, bool excludeSelfForBreak = true)
            where searched : Component
            where breakComp : Component
        {
            List<searched> comps = new List<searched>();
            if(!excludeSelfForBreak)
            {
                if (obj.GetComponent<breakComp>() != null)
                    return comps;
            }
            if(!excludeOwnSearched)
                comps.AddRange(obj.GetComponents<searched>());
            foreach (Transform child in obj)
                comps.AddRange(GetComponentsInChildren<searched, breakComp>(child, false, false));
            return comps;
        }
        public static List<searched> GetComponentsInChildren<searched, breakComp0, breakComp1>(Transform obj, 
            bool excludeOwnSearched = false, bool excludeSelfForBreak = true)
            where searched : Component
            where breakComp0 : Component
            where breakComp1 : Component
        {
            List<searched> comps = new List<searched>();
            if(!excludeSelfForBreak)
            {
                if (obj.GetComponent<breakComp0>() != null)
                    return comps;
                if (obj.GetComponent<breakComp1>() != null)
                    return comps;
            }
            if(!excludeOwnSearched)
                comps.AddRange(obj.GetComponents<searched>());
            foreach (Transform child in obj)
                comps.AddRange(GetComponentsInChildren<searched, breakComp0, breakComp1>(child, false, false));
            return comps;
        }
        
        
        public static List<Component> GetComponentsInChildren(
            Transform obj,
            Type searchedType,
            Type breakType,
            bool excludeOwnSearched = false,
            bool excludeSelfForBreak = true)
        {
            List<Component> comps = new List<Component>();

            // prüfen auf break component
            if (!excludeSelfForBreak)
            {
                if (breakType != null && obj.GetComponent(breakType) != null)
                    return comps;
            }

            // eigene searched hinzufügen
            if (!excludeOwnSearched)
            {
                Component[] found = obj.GetComponents(searchedType);
                comps.AddRange(found);
            }

            // rekursiv durch Kinder
            foreach (Transform child in obj)
            {
                comps.AddRange(GetComponentsInChildren(
                    child,
                    searchedType,
                    breakType,
                    false,
                    false));
            }

            return comps;
        }
        
        
        public static IEnumerator MoveSmooth(Transform obj, Vector3 targetPos, float time) {
            Vector3 startPos = obj.position;
            float t = 0;
            while (t < 1) {
                t += Time.deltaTime / time;
                // Mit SmoothStep wirkt es noch natürlicher (langsam anfahren & abbremsen)
                float smoothT = Mathf.SmoothStep(0, 1, t); 
                obj.position = Vector3.Lerp(startPos, targetPos, smoothT);
                yield return null;
            }
        }
        
        
        public static bool AttributeOverridden(Component comp, string propertyPath)
        {
            var mods = PrefabUtility.GetPropertyModifications(comp);
            if (mods == null) return false;

            foreach (var m in mods)
            {
                if (m.propertyPath == propertyPath)
                    return true;
            }

            return false;
        }
        
        
        public static int GetHighestEnumBit<T>() where T : Enum
        {
            int maxValue = 0;

            foreach (var value in Enum.GetValues(typeof(T)))
            {
                int intValue = Convert.ToInt32(value);
                if (intValue > maxValue)
                {
                    maxValue = intValue;
                }
            }

            int index = 0;

            while (maxValue > 0)
            {
                maxValue >>= 1;
                index++;
            }

            return index;
        }
        
        
        public static int GetHighestFlagBitOffset(int flag)
        {
            int i = 0;
            while(true)
            {
                if(flag == 0)
                    return i;
                flag >>= 1;
                i++;
            }
        }
        
        
        public static List<int> GetFlagIndexes(int flag)
        {
            List<int> indexes = new();
            
            int i = 0;
            while(flag > 0)
            {
                if(flag % 2 == 1)
                    indexes.Add(i);
                flag >>= 1;
                i++;
            }
            return indexes;
        }
        
        
        
        
        
        
        
        
    }
}