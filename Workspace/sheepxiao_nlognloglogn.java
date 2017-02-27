import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.HashMap;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;
import java.util.Map;
import java.util.Map.Entry;
import java.io.BufferedReader;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        GraphQuery solver = new GraphQuery();
        int testCount = Integer.parseInt(in.next());
        for (int i = 1; i <= testCount; i++)
            solver.solve(i, in, out);
        out.close();
    }
    
    static class GraphQuery {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int[] colors = new int[in.nextInt()];
            Edge[] edges = new Edge[in.nextInt()];
            for (int i = 0; i < colors.length; ++i) {
                colors[i] = in.nextInt();
            }
            for (int i = 0; i < edges.length; ++i) {
                edges[i] = new Edge(in.nextInt() - 1, in.nextInt() - 1, in.nextInt());
            }
            
            Array<Cluster> clusters = go(colors, edges);
            
            out.println("Case #" + testNumber + ":");
            int q = in.nextInt();
            int lastAnswer = 0;
            for (; q > 0; --q) {
                int node = (in.nextInt() ^ lastAnswer) - 1;
                int cost = in.nextInt() ^ lastAnswer;
                
                lastAnswer = getRoot(clusters, node, cost).answer;
                out.println(lastAnswer);
            }
        }
        
        private Array<Cluster> go(int[] colors, Edge[] edges) {
            Arrays.sort(edges);
            ComponentStat[] components = new ComponentStat[colors.length];
            Array<Cluster> clusters = new Array<>(colors.length);
            
            for (int i = 0; i < colors.length; ++i) {
                components[i] = new ComponentStat(colors[i]);
                clusters.add(i, new Cluster(i, colors[i], 1), Integer.MIN_VALUE);
            }
            
            for (Edge edge : edges) {
                Cluster cluster1 = getRoot(clusters, edge.from, Integer.MAX_VALUE);
                Cluster cluster2 = getRoot(clusters, edge.to, Integer.MAX_VALUE);
                if (cluster1.parent != cluster2.parent) {
                    if (cluster1.size > cluster2.size) {
                        Cluster cluster = cluster1;
                        cluster1 = cluster2;
                        cluster2 = cluster;
                    }
                    components[cluster2.parent] = components[cluster2.parent].mergeWith(components[cluster1.parent]);
                    Cluster newCluster1 = new Cluster(cluster2.parent, -1, -1);
                    clusters.add(cluster1.parent, newCluster1, edge.cost);
                    
                    Cluster newCluster2 = new Cluster(cluster2.parent, components[cluster2.parent].minId, cluster1.size + cluster2.size);
                    clusters.add(cluster2.parent, newCluster2, edge.cost);
                }
            }
            return clusters;
        }
        
        private Cluster getRoot(Array<Cluster> clusters, int node, int time) {
            while (true) {
                Cluster current = Integer.MAX_VALUE == time ? clusters.get(node) : clusters.get(node, time);
                if (current.parent == node) {
                    return current;
                }
                node = current.parent;
            }
        }
        
    }
    
    static class ComponentStat {
        Map<Integer, Integer> colors;
        int maxNumber;
        int minId;
        
        ComponentStat(int color) {
            this.maxNumber = 1;
            this.minId = color;
            colors = new HashMap<>();
            colors.put(color, 1);
        }
        
        void updateMaxColor(int number, int id) {
            if (number > maxNumber || (number == maxNumber && id < minId)) {
                maxNumber = number;
                minId = id;
            }
        }
        
        ComponentStat mergeWith(ComponentStat o) {
            if (colors.size() < o.colors.size()) {
                return o.mergeWith(this);
            }
            updateMaxColor(o.maxNumber, o.minId);
            for (Map.Entry<Integer, Integer> entry : o.colors.entrySet()) {
                int count = entry.getValue();
                if (colors.containsKey(entry.getKey())) {
                    count += colors.get(entry.getKey());
                }
                colors.put(entry.getKey(), count);
                updateMaxColor(count, entry.getKey());
            }
            return this;
        }
        
    }
    
    static class InputReader {
        BufferedReader reader;
        StringTokenizer tokenizer;
        
        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream));
            tokenizer = null;
        }
        
        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (Exception e) {
                    throw new UnknownError();
                }
            }
            return tokenizer.nextToken();
        }
        
        public int nextInt() {
            return Integer.parseInt(next());
        }
        
    }
    
    static class Array<T> {
        List<Array.Element<T>>[] elements;
        
        public Array(int size) {
            elements = new List[size];
            for (int i = 0; i < elements.length; ++i) {
                elements[i] = new ArrayList<>();
            }
        }
        
        public void add(int at, T value, int time) {
            List<Array.Element<T>> element = elements[at];
            assert (element.isEmpty() || time > element.get(element.size() - 1).time);
            element.add(new Array.Element<>(value, time));
        }
        
        public T get(int at) {
            return elements[at].get(elements[at].size() - 1).value;
        }
        
        public T get(int at, int time) {
            List<Array.Element<T>> element = elements[at];
            int left = 0, right = element.size() - 1;
            while (left < right) {
                int mid = ((left + right) >> 1) + 1;
                if (element.get(mid).time <= time) {
                    left = mid;
                } else {
                    right = mid - 1;
                }
            }
            return element.get(left).value;
        }
        
        static class Element<T> {
            T value;
            int time;
            
            public Element(T value, int time) {
                this.value = value;
                this.time = time;
            }
            
        }
        
    }
    
    static class Edge implements Comparable<Edge> {
        int from;
        int to;
        int cost;
        
        Edge(int from, int to, int cost) {
            this.from = from;
            this.to = to;
            this.cost = cost;
        }
        
        
        public int compareTo(Edge o) {
            return cost - o.cost;
        }
        
    }
    
    static class Cluster {
        int parent;
        int size;
        int answer;
        
        Cluster(int parent, int answer, int size) {
            this.parent = parent;
            this.answer = answer;
            this.size = size;
        }
        
    }
}
