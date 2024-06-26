import math
import time

def calculate_path_cost(path):
    costs = {
        'AB': 2 + 3 * 4 - 5 / 10 + 5**2,
        'AC': 2**3 + 4 * 5 - 6 /10 + 1,
        'BC': 5 * 4 - 2 + 5**2 - 7,
        'BD': 3 + 4 * 5 - 8 / 2 + 1,
        'CD': 3**3 + 8 - 5 * 3 + 8
    }
    return math.ceil(costs[path])

def traverse_maze(route, gold):
    room_gold = {'A': 40, 'B': 50, 'C': 75, 'D': 100}
    total_gold = gold

    print(f"\nTrying route: {' -> '.join(route)}")
    print(f"Starting gold: {total_gold}")
    time.sleep(0.25)

    for i in range(len(route) - 1):
        current_room, next_room = route[i], route[i+1]
        path = ''.join(sorted(current_room + next_room))
        path_cost = calculate_path_cost(path)
        
        print(f"\nMoving from {current_room} to {next_room}. Path cost: {path_cost}")
        time.sleep(0.25)

        if total_gold < path_cost:
            print("Not enough gold to proceed!")
            time.sleep(0.25)
            return 0  # cant keep going if gold becomes negative
        
        total_gold -= path_cost
        print(f"Paid {path_cost} gold. Remaining gold: {total_gold}")
        time.sleep(0.25)

        total_gold += room_gold[next_room]
        print(f"Collected {room_gold[next_room]} gold from room {next_room}. New total: {total_gold}")
        time.sleep(0.25)

    return total_gold

def find_optimal_route():
    possible_routes = [
        ['A', 'B', 'D'],
        ['A', 'C', 'D'],
        ['A', 'B', 'C', 'D'],
        ['A', 'C', 'B', 'D']
    ]

    max_gold = 0
    optimal_route = []

    for route in possible_routes:
        gold = traverse_maze(route, 40)  # start with 40 gold in room A
        print(f"\nRoute {' -> '.join(route)} finished with {gold} gold")
        time.sleep(0.25)
        if gold > max_gold:
            max_gold = gold
            optimal_route = route

    return ''.join(optimal_route), max_gold

optimal_route, max_gold = find_optimal_route()
print(f"\nOptimal route: {optimal_route}")
print(f"Maximum gold: {max_gold}")