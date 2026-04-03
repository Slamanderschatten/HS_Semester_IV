using UnityEngine;

namespace utils
{
    public class MoveRigidBodyCenter : MonoBehaviour
    {
        public Vector3 centerOffcet;
        
        private void Awake()
        {
            GetComponent<Rigidbody>().centerOfMass += centerOffcet;
            Destroy(this);
        }
    }
}