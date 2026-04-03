using UnityEngine;
using utils.pattern.option;

namespace npc
{
    public class NPC : MonoBehaviour
    {
        private Knowledge knowledge;
        private OptionMgmt<NPC, NpcOption> options;
        private Consideration consideration;
        private Reasoner reasoner;

        protected virtual void Awake()
        {
            knowledge = new(this);
            options = new(this);
            consideration = new(this);
            reasoner = new(this);
        }
        
        
        public Knowledge Knowledge => knowledge;
        public OptionMgmt<NPC, NpcOption> Options => options;
        public Consideration Consideration => consideration;
        public Reasoner Reasoner => reasoner;
        
        
        
        



    }
}