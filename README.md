# �����㷨���۵ڶ���α�����C����ʵ��

## ˵��һ
    ÿ���㷨����4���ļ�����XXX.h XXX.c XXX.mk XXX_test.c �ļ���XXXΪ�㷨�����ƣ�XXX_test.c Ϊ�����㷨��Ч�Ե��ļ�����main�������ڵ��ļ���makefileΪgnu make��ʹ��auto-c-files.el(Emacs-Lisp����)��������4���ļ���������Ӧ��ģ�塣auto_make_template.mkΪmakefile��ģ�塣

## ˵����
    ͼ��ʵ��Ϊ�ڽ���������ڽӾ����ڶ�ͼ���в���ʱ��ʹ�õ����������ʽ���£�
### �ڽӾ���(�����������ļ�adj_table.datΪ��)

      // �������������0��ʼ����������
      0  // ͼ�������������������ʾ
      2  // ��һ����ʾ�Ķ���ĳ���
      1 4  // ����������ʾ�Ķ���ΪԴ�㣬��֮�������ڽӶ���
      1    // �ڶ������������
      4
      0 2 3 4
      2
      2
      1 3
      3
      3
      1 2 4
      4
      3
      0 1 3 // �ļ������һ��������ֹ������û�л��з�

      ����adj_output()����Ľ��Ϊ��

      5
      0 -> 1, weight: 0; 0 -> 4, weight: 0; 
      1 -> 0, weight: 0; 1 -> 4, weight: 0; 1 -> 3, weight: 0; 1 -> 2, weight: 0; 
      2 -> 1, weight: 0; 2 -> 3, weight: 0; 
      3 -> 1, weight: 0; 3 -> 4, weight: 0; 3 -> 2, weight: 0; 
      4 -> 0, weight: 0; 4 -> 3, weight: 0; 4 -> 1, weight: 0;

### �ڽӾ���(�����������ļ�all_pair_shortest_path.datΪ��)

      5  // ����ĸ�������������Ϊ��0��ʼ�������������˴�Ϊ0~4
      0 1 3  // edge: 0 -> 1 weight: 3
      0 2 8  // edge: 0 -> 2 weight: 8
      0 4 -4 // etc ...
      1 3 1
      1 4 7
      2 1 4
      3 0 2
      3 2 -5
      4 3 6 // �ļ������һ��������ֹ������û�л��з�
      ����print_adjmat()���Ϊ��

      adj_mat_test all_pair_shortest_path.dat 
      |0   3   8   INF -4  |
      |INF 0   INF 1   7   |
      |INF 4   0   INF INF |
      |2   INF -5  0   INF |
      |INF INF INF 6   0   |

## ˵����

    ���㷨���۵ڶ��������α���벢û����ȫʵ�֣�û�ж���ϰ��Ĵ𰸽��д���ʵ�֡����뻹�кܶ�Ľ��ĵط�����һ�µ�����Լ����һ�µĺ����ӿڣ���ƵĹ淶�Եȵȡ���Щ�������ں����ĸĶ������ܱ��벻��ͨ����������ʱ����һ���Ľ�����������Emacs for Windows + MinGW + GCC����Դ�����ѧϰ����֮�ã�����������Ŀ�ģ�ά���߸Ų����𡣻�ӭ��Դ������Ȥ��ͬѧ��������:).
***
# �㷨����
  1. �����㷨
     * ������		heap_sort
     * ��������		quick_sort
  2. �������ݽṹ
     * ջ		stack
     * ����		queue
     * ����		list
     * �ڽ�����		adj_table
     * �ڽӾ���		adj_mat
  3. ��
     * ���������		bst
     * �����     	rbtree
  4. ��
     * �����		binomial_heap
     * Fibonacci��	fib_heap
  5. ��̬�滮
     * 0-1 ��������	knapsack
     * �����������	lcs
  6. ̰���㷨(������)
  7. ͼ�㷨
     * �����������	bfs
     * �����������	dfs
     * ��������		toplogical_sort
     * ǿ��ͨ��֧		scc
     * ��С������		mst_prim, mst_kruskal
     * ��Դ���·��	single_source_shortest_path bellman_ford, dijkstra
     * ÿ�Զ�������·��	all_pair_shortest_path, floyd_warshall, johnson
     * ����ͼ�Ĵ��ݱհ�	transitive_closure    
     * �����		ford_fulkerson
      
