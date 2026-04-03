using System;
using System.Diagnostics.CodeAnalysis;
using UnityEngine;
using UnityEngine.Events;

namespace utils.pattern.subscribe
{
    [Serializable]
    public class Subscriber<publisherT, subscriberT> 
        where publisherT : class, Publisher<publisherT, subscriberT>.IHolder
        where subscriberT : class
    {
        
        public subscriberT Holder {get;}
        protected Publisher<publisherT, subscriberT> publisher;
        protected Func<publisherT> findParent;
        
        
        public UnityEvent<subscriberT> onSubscribe = new();
        public UnityEvent<subscriberT> onUnsubscribe = new();
        
        
        
        
        public Subscriber([NotNull]subscriberT holder, [NotNull]Func<publisherT> findParentFunc)
        {
            Holder = holder;
            findParent = findParentFunc;
        }
        public Subscriber([NotNull]subscriberT holder)
        {
            Holder = holder;
        }
        
        
        public virtual bool FindPublisher()
        {
            var newPublisher = findParent();
            if(newPublisher == Publisher)
                return Publisher != null;
            Unsubscribe();
            Subscribe(newPublisher.GetPublisherForSubscriber<subscriberT>());
            return publisher != null;
        }
        
        
        protected virtual void Subscribe(Publisher<publisherT, subscriberT> newPublisher)
        {
            publisher = newPublisher;
            if(publisher == null)
                return;
            try{onSubscribe?.Invoke(Holder);}catch(Exception e){Debug.LogException(e);}
            publisher.Subscribe(this);
        }
        
        
        public virtual void Unsubscribe()
        {
            if(publisher == null)
                return;
            try{onUnsubscribe?.Invoke(Holder);}catch(Exception e){Debug.LogException(e);}
            publisher.Unsubscribe(this);
            publisher = null;
        }
        
        
        public publisherT Publisher => publisher?.Holder;
        
        
        
    }
    
    
    
    
    
    
    [Serializable]
    public class MonoBehaviorSubscriber<publisherT, subscriberT> : Subscriber<publisherT, subscriberT>
        where publisherT : MonoBehaviour, Publisher<publisherT, subscriberT>.IHolder
        where subscriberT : MonoBehaviour
    {
        public MonoBehaviorSubscriber([NotNull]subscriberT holder) : base(holder)
        {
            findParent = FindPublisherInParent;
        }


        private publisherT FindPublisherInParent()
        {
            return Holder.transform.GetComponentInParent<publisherT>();
        }
        
        
        
    }
    
    
}