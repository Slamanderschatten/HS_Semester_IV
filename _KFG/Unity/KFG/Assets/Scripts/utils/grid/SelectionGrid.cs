using System;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using utils.grid.gridSpotOptions;

namespace utils.grid
{
    public class SelectionGrid
    {
        const float AngleArea = 17f;
        
        public bool Enabled {get; private set;} = true;
        public float DirectionAreaAngle {get; set;} = 45f;
        public int InsertsPerFrame {get; set;} = int.MaxValue;
        
        
        //events
        public delegate void SpotChangeHandle(GridSpot spotBefore, GridSpot spotNow);
        public delegate void SpotSelectableChangeHandle(GridSpot spotBefore, GridSpot spotNow);
        public delegate void SelectionGridHandle(SelectionGrid grid, ChangeSituation situation);
        public event SpotChangeHandle OnChangeFocusedSpot;
        public event SpotSelectableChangeHandle OnChangeSelectedSpot;
        public event SelectionGridHandle OnGridActualized;
        
        //conditions
        public delegate bool SpotPossibleHandle(GridSpot spot);
        public event SpotPossibleHandle ConditionFocusPossible;
        
        
        private readonly List<Node> graph = new();
        public IReadOnlyList<Node> NodeList => new List<Node>(graph);
        
        //focus
        private Node attr_focusedNode;
        public GridSpot FocusedSpot => FocusedNode?.spot;
        
        //selection
        private GridSpot attr_selectedSpot;
        
        
        
        public virtual void Enable()
        {
            Enabled = true;
        }
        public virtual void Disable()
        {
            Enabled = false;
            Reset();
        }
        
        
        protected virtual Node AddSpotIntern(GridSpot spot)
        {
            spot.Grid = this;
            if(!spot.Is<Focusable>())
                return null;
            Node existing = graph.Find(n => n.spot == spot);
            if(existing != null)
                return existing;
            AddNode(new Node{spot = spot, edges = new List<Edge>()});
            return graph[^1];
        }
        
        
        protected virtual void AddNode(Node newNode)
        {
            InsertNode(newNode, graph);
            graph.Add(newNode);
        }
        
        
        public virtual Node AddSpot(GridSpot spot)
        {
            var ret = AddSpotIntern(spot);
            try{OnGridActualized?.Invoke(this, ChangeSituation.InsertSpot);}catch(Exception e){Debug.LogException(e);}
            return ret;
        }
        
        
        public virtual void RemoveSpot(GridSpot spot)
        {
            int index = graph.FindIndex(n => n.spot == spot);
            if(index < 0)
                return;
            RemoveNode(index);
            try{OnGridActualized?.Invoke(this, ChangeSituation.RemoveSpot);}catch(Exception e){Debug.LogException(e);}
        }
        
        
        public virtual void ActualizeSpot(GridSpot spot)
        {
            foreach (Node node in graph)
            {
                if(node.spot == spot)
                {
                    RemoveNode(node);
                    AddNode(node);
                    try{OnGridActualized?.Invoke(this, ChangeSituation.ActualizeSpot);}catch(Exception e){Debug.LogException(e);}
                    return;
                }
            }            
        }
        
        
        public virtual void IntegrateSpot(GridSpot spot)
        {
            ActualizeSpot(spot);
        }
        
        
        public virtual void SetSpots(GridSpot[] spots)
        {
            ClearIntern();
            foreach (GridSpot spot in spots)
                AddSpotIntern(spot);
            try{OnGridActualized?.Invoke(this, ChangeSituation.ActualizeAll);}catch(Exception e){Debug.LogException(e);}
        }
        
        
        public virtual Node GetNodeFrom(GridSpot gridSpot)
            => graph.Find(n => n.spot == gridSpot);
        
        
        public virtual void ActualizeNeighbours()
        {
            ClearAllNeighboursIntern();
            ActualizeSubGraphNeighbours(graph);
            try{OnGridActualized?.Invoke(this, ChangeSituation.ActualizeAll);}catch(Exception e){Debug.LogException(e);}
        }
        public virtual IEnumerator ActualizeNeighboursAsync()
        {
            ClearAllNeighboursIntern();
            yield return ActualizeSubGraphNeighboursAsync(graph);
            try{OnGridActualized?.Invoke(this, ChangeSituation.ActualizeAll);}catch(Exception e){Debug.LogException(e);}
        }
        
        
        public virtual void Clear()
        {
            ClearIntern();
            try{OnGridActualized?.Invoke(this, ChangeSituation.ClearAll);}catch(Exception e){Debug.LogException(e);}
        }
        
        
        public virtual void ClearEdges()
        {
            ClearAllNeighboursIntern();
            try{OnGridActualized?.Invoke(this, ChangeSituation.ActualizeAll);}catch(Exception e){Debug.LogException(e);}
        }
        
        
        /******************************************* generation **********************************************/
        
        
        private void ResetNode(Node node)
        {
            if(node == FocusedNode)
                FocusedNode = null;
            if(node.spot == SelectedSpot)
                SelectedSpot = null;
            ClearNeighboursIntern(node);
        }
        
        
        private void ClearNeighboursIntern(Node node)
        {
            for(int i = node.edges.Count-1; i >= 0; i--)
                node.edges[i].Delete();
        }
        
        
        protected virtual void ActualizeSubGraphNeighbours(List<Node> subGraph)
        {
            List<Node> integrated = new();
            foreach (Node a in subGraph)
            {
                InsertNode(a, integrated);
                integrated.Add(a);
            }
        }
        protected virtual IEnumerator ActualizeSubGraphNeighboursAsync(List<Node> subGraph)
        {
            List<Node> integrated = new();
            int c = 0;
            foreach (var node in subGraph)
            {
                if(++c % InsertsPerFrame == 0)
                {
                    yield return null;
                    c=0;
                }
                InsertNode(node, integrated);
                integrated.Add(node);
            }
        }
        
        
        private void InsertNode(Node node, List<Node> subGraph)
        {
            if(!node.spot.Is<Focusable>())
                return;
            List<Edge> newEdges = new();
            foreach (Node b in subGraph)
            {
                if(node == b)
                    continue;
                node.edges.Find(e => e.Other(node) == b)?.Delete(); //delete existing for a clean include
                if(ProveEdge(node, b, subGraph, out float distAtoB, out var intersectionEdges))
                {
                    Edge newEdge = new Edge(node, b, distAtoB);
                    node.edges.Add(newEdge);
                    newEdges.Add(newEdge);
                    //remove intersection edges / backward iteration because of the deletion
                    foreach(Edge e in intersectionEdges)
                        e.Delete();
                }
            }
            //add node to neighbours after the last edge is proved
            foreach (Edge edge in newEdges)
                edge.AddSelfToNode2();
        }
        
        
        private bool ProveEdge(Node a, Node b, List<Node> comparisonList, out float distAtoB, out List<Edge> intersectionEdges)
        {
            intersectionEdges = new List<Edge>();
            distAtoB = (b.Pos - a.Pos).magnitude;
            foreach (Node c in comparisonList)
            {
                if(c == b)
                    continue;
                foreach (Edge edge in c.edges)
                {
                    Node d = edge.Other(c);
                    if (b == d ||  //no duplicated proves or connected edges
                        !IntersectionCheck(
                            a, b, distAtoB, 
                            c, d, edge.dist, 
                            out byte nearestPoint))
                        continue;
                    if(nearestPoint > 1)
                        // Break as soon as it is known that the connection will not be established
                        return false;
                        
                    intersectionEdges.Add(edge);
                }
            }
            
            return true;
        }
        
        
        private bool IntersectionCheck(
            Node start1, Node end1, float length1, 
            Node start2, Node end2, float length2, 
            out byte nearestPoint)
        {
            nearestPoint = 0; //undefined

            Vector2 p = start1.Pos;
            Vector2 r = end1.Pos - p;

            Vector2 q = start2.Pos;
            Vector2 s = end2.Pos - q;

            float rxs = r.x * s.y - r.y * s.x;
            if (Mathf.Approximately(rxs, 0f))
                return false; // collinear

            Vector2 qp = q - p;
            float t = (qp.x * s.y - qp.y * s.x) / rxs;
            if (t < 0f || t > 1f)
                return false; // outside Segment 1

            float u = (qp.x * r.y - qp.y * r.x) / rxs;
            if (u < 0f || u > 1f)
                return false; // outside Segment 2

            // determine nearest point
            float tLen = t * length1;
            float invTLen = length1 - tLen;

            float uLen = u * length2;
            float invULen = length2 - uLen;

            float minDist = tLen;

            if (invTLen < minDist)
            {
                minDist = invTLen;
                nearestPoint = 1;
            }

            if (uLen < minDist)
            {
                minDist = uLen;
                nearestPoint = 2;
            }

            if (invULen < minDist)
            {
                nearestPoint = 3;
            }

            return true;
        }
        
        
        protected void RemoveNode(Node node)
        {
            List<Node> neighbours = node.Neighbours;
            ResetNode(node);
            graph.Remove(node);
            ActualizeSubGraphNeighbours(neighbours);
        }
        protected void RemoveNode(int nodeIndex)
        {
            Node node = graph[nodeIndex];
            List<Node> neighbours = node.Neighbours;
            ResetNode(graph[nodeIndex]);
            graph.RemoveAt(nodeIndex);
            ActualizeSubGraphNeighbours(neighbours);
        }
        
        
        protected virtual void ClearIntern()
        {
            FocusedNode = null;
            SelectedSpot = null;
            graph.Clear();
        }
        
        
        protected virtual void ClearAllNeighboursIntern()
        {
            foreach (Node node in graph)
                node.edges.Clear();
        }
        
        
        /******************************************* selection *******************************************************/
        
        
        public virtual GridSpot GoToNearest(Vector2 position, out bool switched)
        {
            if(graph.Count == 0 || !Enabled)
            {
                switched = false;
                return null;
            }
            FocusedNode ??= graph[0];
            bool nearestFound = false;
            switched = false;
            while(!nearestFound) // walk over more than one place if necessary
            {
                nearestFound = true;
                float distance = Vector2.Distance(FocusedNode.spot.Pos, position);
                foreach (Node neighbour in FocusedNode.Neighbours)
                {
                    if(Vector2.Distance(neighbour.spot.Pos, position) < distance)
                    {
                        FocusedNode = neighbour;
                        nearestFound = false;
                        switched = true;
                        break;
                    }
                }
            }
            return FocusedNode.spot;
        }
        
        
        public virtual GridSpot GoToNearest(Vector2 position)
            => GoToNearest(position, out _);
        
        
        public virtual GridSpot GoToDirection(Vector2 direction)
        {
            if(NodeList.Count == 0 || !Enabled)
                return null;
            if(FocusedNode == null)
            {
                FocusedNode = graph[0];
                return FocusedNode.spot;
            }
            
            List<Node> possibleNeighbours = GetPossibleNeighbours(FocusedNode);
            
            float bestAngle = float.MaxValue;
            float bestDist = float.MaxValue;
            Node bestNode = FocusedNode;

            foreach (Node neighbour in possibleNeighbours)
            {
                Vector2 neighbourDir = neighbour.spot.Pos - FocusedNode.spot.Pos;
                float angle = Vector2.Angle(direction, neighbourDir);
                float dist = neighbourDir.magnitude;
                
                if(angle < bestAngle)
                {
                    if(bestAngle > AngleArea || dist < bestDist)
                    {
                        bestAngle = angle;
                        bestNode = neighbour;
                        bestDist = dist;
                    }
                }
            }
            
            if(bestAngle <= DirectionAreaAngle)
                FocusedNode = bestNode;
            return FocusedNode.spot;
        }
        
        
        protected virtual List<Node> GetPossibleNeighbours(Node node)
        {
            List<Node> possibleNeighbours = new();
            Queue<Node> neighboursToProve = new();
            HashSet<Node> proved = new();
            foreach (Edge edge in node.edges)
                neighboursToProve.Enqueue(edge.Other(node));;
            Node neighbour = neighboursToProve.Dequeue();
            while(neighbour != null)
            {
                if(!proved.Add(neighbour))
                    continue;
                if(ConditionFocusPossible?.Invoke(neighbour.spot) ?? true)
                    possibleNeighbours.Add(neighbour);
                else
                {
                    foreach (Edge edge in neighbour.edges)
                        neighboursToProve.Enqueue(edge.Other(neighbour));
                }
                
                neighbour = neighboursToProve.Dequeue();
            }
            return possibleNeighbours;
        }
        
        
        public virtual bool Select(GridSpot spot)
        {
            if(!Enabled)
                return false;
            SelectedSpot = spot;
            return SelectedSpot == spot;
        }
        public virtual bool Select()
        {
            TriggerFocused();
            if(FocusedSpot ==  null)
                return false;
            return Select(FocusedSpot);
        }
        
        
        public virtual void TriggerFocused()
        {
            FocusedSpot?.Get<Trigger>()?.RunTrigger();
        }
        
        
        public virtual void Deselect()
        {
            SelectedSpot = null;
        }
        
        
        public virtual void UnFocus()
        {
            FocusedNode = null;
        }
        
        
        public virtual void Reset()
        {
            Deselect();
            UnFocus();
        }
        
        
        protected Node FocusedNode
        {
            get => attr_focusedNode;
            private set
            {
                if(value == attr_focusedNode)
                    return;
                
                GridSpot old = attr_focusedNode?.spot;
                GridSpot newSpot = value?.spot;
                old?.Get<Focusable>().UnFocus();
                attr_focusedNode = value;
                newSpot?.Get<Focusable>().Focus();
                try{OnChangeFocusedSpot?.Invoke(old, newSpot); }catch(Exception e){Debug.LogException(e);}
            }
        }
        
        
        public GridSpot SelectedSpot
        {
            get => attr_selectedSpot;
            private set
            {
                if(value == attr_selectedSpot)
                    return;
                
                if(value == null)
                {
                    //reset selected
                    attr_selectedSpot?.Get<Selectable>()?.UnSelect();
                    attr_selectedSpot = null;
                    try{OnChangeSelectedSpot?.Invoke(attr_selectedSpot, null); }catch(Exception e){Debug.LogException(e);}
                    return;
                }
                
                Selectable selectOption = value.Get<Selectable>();
                if(selectOption == null)
                    return; //spot is not selectable
                
                //switch selection
                GridSpot old = attr_selectedSpot;
                old?.Get<Selectable>()?.UnSelect();
                attr_selectedSpot = value;
                selectOption.Select();
                try{OnChangeSelectedSpot?.Invoke(old, attr_selectedSpot); }catch(Exception e){Debug.LogException(e);}
            }
        }
        
        
        
        
        
        
        
        
        
        
        
        public enum ChangeSituation
        {
            ActualizeAll = 1,
            ClearAll = 2,
            InsertSpot = 3,
            RemoveSpot = 4,
            ActualizeSpot = 5,
        }
        
        
        public class Edge
        {
            public readonly Node node1;
            public readonly Node node2;
            public readonly float dist;
            
            
            
            public Node Other(Node node) => node == node1 ? node2 : node1;
            
            
            public Edge(Node node1, Node node2)
            {
                this.node1 = node1;
                this.node2 = node2;
                dist = float.MaxValue;
            }
            public Edge(Node node1, Node node2, float dist)
            {
                this.node1 = node1;
                this.node2 = node2;
                this.dist = dist;
            }
            
            
            public void Delete()
            {
                node1.edges.Remove(this);
                node2.edges.Remove(this);
            }
            
            
            public void AddSelfToNode1() => node1.edges.Add(this);
            public void AddSelfToNode2() => node2.edges.Add(this);
            
            
        }
        
        
        public class Node
        {
            public GridSpot spot;
            public List<Edge> edges;
            
            public List<Node> Neighbours
            {
                get
                {
                    List<Node> neighbours = new();
                    foreach (Edge edge in edges)
                        neighbours.Add(edge.Other(this));
                    return neighbours;
                }
            }
            
            public Vector2 Pos => spot.Pos;
        }
        
        
        
        
        
        
        
        
        
        
        
    }
}