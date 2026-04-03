using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using UnityEngine;
using UnityEngine.Events;
using Object = UnityEngine.Object;

namespace utils.pattern.subscribe
{
    [Serializable]
    public class Publisher<publisherT, subscriberT> : IEnumerable<subscriberT> 
        where publisherT : class, Publisher<publisherT, subscriberT>.IHolder
        where subscriberT : class
    {
        public publisherT Holder {get;}
        protected readonly List<Subscriber<publisherT, subscriberT>> subscribers = new();
        
        public UnityEvent<subscriberT> onSubscribed = new();
        public UnityEvent<subscriberT> onUnsubscribed = new();
        
        
        public Publisher([NotNull]publisherT holder)
        {
            Holder = holder;
        }
        
        
        public void Subscribe(Subscriber<publisherT, subscriberT> subscriber)
        {
            subscribers.Add(subscriber);
            try{onSubscribed?.Invoke(subscriber.Holder);}catch(Exception e){Debug.LogException(e);}
        }
        
        
        public void Unsubscribe(Subscriber<publisherT, subscriberT> subscriber)
        {
            subscribers.Remove(subscriber);
            try{onUnsubscribed?.Invoke(subscriber.Holder);}catch(Exception e){Debug.LogException(e);}
        }


        public IEnumerator<subscriberT> GetEnumerator()
        {
            foreach (Subscriber<publisherT, subscriberT> subscriber in subscribers)
                yield return subscriber.Holder;
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
        
        
        public subscriberT this[int index] => subscribers[index].Holder;
        
        public int Count => subscribers.Count;
        
        
        
        
        
        
        public interface IHolder
        {
            public Publisher<publisherT, subscriberT> GetPublisherForSubscriber<subscriberType>();
        }
        
        
        
        
    }
    
}