import csv
from dbfread import DBF

def read_nodes(filename):
    nodes = {}
    for record in DBF(filename, encoding='utf-8'):
        osmid = int(record['osmid'])
        y = float(record['y'])
        x = float(record['x'])
        nodes[osmid] = {'y': y, 'x': x}
    return nodes

def read_edges(filename):
    edges = []
    for record in DBF(filename, encoding='utf-8'):
        u = int(record['u'])
        v = int(record['v'])
        edges.append({'u': u, 'v': v})
    return edges

def save_to_csv(nodes, edges, filename):
    with open(filename, 'w', newline='') as csvfile:
        fieldnames = ['p1_x', 'p1_y', 'p2_x', 'p2_y']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

        writer.writeheader()
        for edge in edges:
            u = edge['u']
            v = edge['v']
            writer.writerow({'p1_x': nodes[u]['x'], 'p1_y': nodes[u]['y'], 'p2_x': nodes[v]['x'], 'p2_y': nodes[v]['y']})

def main():
    nodes_file = 'nodes.dbf'
    edges_file = 'edges.dbf'
    output_file = 'datapy.csv'

    # Read nodes and edges
    nodes = read_nodes(nodes_file)
    edges = read_edges(edges_file)

    # Save nodes and edges to CSV
    save_to_csv(nodes, edges, output_file)

if __name__ == "__main__":
    main()