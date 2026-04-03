using npc;
using UnityEngine;

namespace Testing
{
    public class DebugMgmt : MonoBehaviour
    {


        private void Update()
        {
            if (Input.GetKeyDown(KeyCode.S))
                FindFirstObjectByType<NPC>().Options.FirstOption.Activate();
        }
    }
}