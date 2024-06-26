require 'time'

$costs = {
  'AB' => 2 + 3 * 4 - 5 / 10.0 + 5**2,
  'AC' => 2**3 + 4 * 5 - 6 / 10.0 + 1,
  'BC' => 5 * 4 - 2 + 5**2 - 7,
  'BD' => 3 + 4 * 5 - 8 / 2.0 + 1,
  'CD' => 3**3 + 8 - 5 * 3 + 8
}

$room_gold = { 'A' => 40, 'B' => 50, 'C' => 75, 'D' => 100 }

def traverse_maze(route, gold)
  total_gold = gold

  puts "\nTrying route: #{route.join(' -> ')}"
  puts "Starting gold: #{total_gold}"
  sleep(0.25)

  (0...route.length - 1).each do |i|
    current_room = route[i]
    next_room = route[i + 1]
    path = [current_room, next_room].sort.join
    path_cost = $costs[path].ceil

    puts "\nMoving from #{current_room} to #{next_room}. Path cost: #{path_cost}"
    sleep(0.25)

    if total_gold < path_cost
      puts "Not enough gold to proceed!"
      sleep(0.25)
      return 0
    end

    total_gold -= path_cost
    puts "Paid #{path_cost} gold. Remaining gold: #{total_gold}"
    sleep(0.25)

    total_gold += $room_gold[next_room]
    puts "Collected #{$room_gold[next_room]} gold from room #{next_room}. New total: #{total_gold}"
    sleep(0.25)
  end

  total_gold
end

def find_optimal_route
  possible_routes = [
    ['A', 'B', 'D'],
    ['A', 'C', 'D'],
    ['A', 'B', 'C', 'D'],
    ['A', 'C', 'B', 'D']
  ]

  max_gold = 0
  optimal_route = []

  possible_routes.each do |route|
    gold = traverse_maze(route, 40)
    puts "\nRoute #{route.join(' -> ')} finished with #{gold} gold"
    sleep(0.25)
    if gold > max_gold
      max_gold = gold
      optimal_route = route
    end
  end

  puts "\nOptimal route: #{optimal_route.join}"
  puts "Maximum gold: #{max_gold}"
end

find_optimal_route