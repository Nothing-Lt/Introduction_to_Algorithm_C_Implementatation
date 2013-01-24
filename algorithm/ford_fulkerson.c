// ʵ���������ford_fulkerson����
// ����ʵ�ֲ���Edmonds_Karp�㷨
// ͼ�����ڽ�����ʵ��
// ����Դ�㵽����·��ʹ��bfs�㷨
// ÿ�Զ���������ʹ���ڽӾ����ʾ
// ÿ�Զ���Ĳ�������ʹ���ڽӾ����ʾ
// ���·���ϵĸ�������path[]�����ʾ
#include "ford_fulkerson.h"

// �ٶ�graph��flow�ѷ����ڴ�
// graph�ѳ�ʼ��
void initialize_edge_flow(AdjList* graph, int numVertices, AdjMat* flow)
{
    int i;
    for (i = 0; i < numVertices; i++) {
	AdjListNodePtr x = graph[i];
	while (x) {
	    flow->mat[i][x->vertex] = 0;
	    flow->mat[x->vertex][i] = 0;
	    x = x->next;
	}
    }
}
// �ô�path��ջ����ʾ��
// ʹ��make_stack������Stack
EBool find_shortest_path(AdjList* graph, int numVertices, int s, int t, Stack path)
{
    int *distance = (int *)malloc(numVertices * sizeof(int));
    int *parent = (int *)malloc(numVertices * sizeof(int));
    bfs(graph, numVertices, s, distance, parent);
#ifdef DEBUG
    print_path(graph, numVertices, parent, s, t);
#endif // DEBUG
    return calc_path(graph, numVertices, parent, s, t, path);
}


int rc(int u, int v, AdjMat* f, AdjMat* c)
{
    int rCap = c->mat[u][v] - f->mat[u][v];
    return rCap;
}

int min_res_cap(AdjMat* c, AdjMat*f, Stack path)
{
    int i=0, u, v, min = INFINITE;
    if(peek(path, i++, &u))
    {
	while (peek(path, i++, &v)) {
	    int uv = rc(u, v, f, c);
	    assert(uv > 0);
	    assert(u != v);
	    min = uv < min? uv:min;
	    u = v;
	}	
    }
    return min;
}
void update_flow(AdjMat* f, Stack path, int cfp)
{
    int i = 0, u,v;
    if (peek(path, i++, &u))
    {
	while (peek(path, i++, &v)) {
	    assert(u != v);
	    f->mat[u][v] = f->mat[u][v] + cfp;
	    f->mat[v][u] = -f->mat[u][v];
	    u = v;
	}
    }
}

// ���²�������
void update_residual_graph(AdjList* gQuote, int numVertices, AdjMat* c, AdjMat* f, Stack path)
{
    // ��θ��£�
    // Ҫ����һ���������磬����ͼҪ֧�ֵĹ����ǣ�����һ���ߺͼ���һ����
    // ����������Ҫ���µĲ���ֻ�������·����
    int u, v;
    if (pop(path,&u))
    {
	while (pop(path, &v)) {
	    assert(u !=  v);
	    if (rc(u, v, f, c) > 0)
	    {
		add_edge(gQuote, numVertices, u, v);
	    }
	    else if (rc(u,v,f,c) == 0)
	    {
		assert(del_edge(gQuote, numVertices, u, v) == TRUE);
	    }
	    if (rc(v, u, f, c) > 0)
	    {
		add_edge(gQuote, numVertices, v, u);
	    }
	    else if (rc(v, u, f, c) == 0)
	    {
		assert(del_edge(gQuote, numVertices, v, u) == TRUE);
	    }
	    u = v;
	}
    }
}
// ����
// ���
// �����Ĺ���
// ������
// �ٶ�graph, f��c�ѷ����ڴ�
// graph��c�ѳ�ʼ�����
// ���⣺��ʱ���²���������ֱ�Ӽ��㣬���洢?
// c ��ʾ����ͼ��ʼ��ʱ�����������ǲ�������
void ford_fulkerson(AdjList* gQuote, int numVertices, int s, int t, AdjMat* f, AdjMat* c)
{
    Stack path = make_stack();
    int minResCap;
    //adj_list* gQuote = copy_adjlist(graph, numVertices);
    print_adjlist(gQuote, numVertices);
    initialize_edge_flow(gQuote, numVertices, f);
    print_adjmat(f);
    // ѭ���޷���ֹ
    while (find_shortest_path(gQuote, numVertices, s, t, path)) {
	// ��β鿴ջ�е�����Ԫ�ض��ֲ�ɾ�����Ԫ�أ�
	printf("shortest path found\n");
	print_stack(path);
	printf("\n");
	fflush(stdout);
	minResCap = min_res_cap(c, f,  path);
#ifdef DEBUG
	printf("minResCap = %d\n", minResCap);
#endif // DEBUG
	update_flow(f, path, minResCap);
	printf("updated_flow\n");
	print_adjmat(c);
	print_adjmat(f);
	// ���⣺��δ�G����Gf
	update_residual_graph(gQuote, numVertices, c, f, path);
	print_adjlist(gQuote, numVertices);
	fflush(stdout);
    }
    //freeAdjList(gQuote, numVertices);
}












