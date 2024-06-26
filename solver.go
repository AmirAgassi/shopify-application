package main

import (
	"fmt"
	"math"
	"time"
)

var costs = map[string]float64{
	"AB": 2 + 3*4 - 5/10.0 + math.Pow(5, 2),
	"AC": math.Pow(2, 3) + 4*5 - 6/10.0 + 1,
	"BC": 5*4 - 2 + math.Pow(5, 2) - 7,
	"BD": 3 + 4*5 - 8/2.0 + 1,
	"CD": math.Pow(3, 3) + 8 - 5*3 + 8,
}

var roomGold = map[rune]int{
	'A': 40,
	'B': 50,
	'C': 75,
	'D': 100,
}

func traverseMaze(route []rune, gold int) int {
	totalGold := gold

	fmt.Printf("\nTrying route: %s\n", string(route))
	fmt.Printf("Starting gold: %d\n", totalGold)
	time.Sleep(250 * time.Millisecond)

	for i := 0; i < len(route)-1; i++ {
		currentRoom := route[i]
		nextRoom := route[i+1]
		path := string([]rune{min(currentRoom, nextRoom), max(currentRoom, nextRoom)})
		pathCost := int(math.Ceil(costs[path]))

		fmt.Printf("\nMoving from %c to %c. Path cost: %d\n", currentRoom, nextRoom, pathCost)
		time.Sleep(250 * time.Millisecond)

		if totalGold < pathCost {
			fmt.Println("Not enough gold to proceed!")
			time.Sleep(250 * time.Millisecond)
			return 0
		}

		totalGold -= pathCost
		fmt.Printf("Paid %d gold. Remaining gold: %d\n", pathCost, totalGold)
		time.Sleep(250 * time.Millisecond)

		totalGold += roomGold[nextRoom]
		fmt.Printf("Collected %d gold from room %c. New total: %d\n", roomGold[nextRoom], nextRoom, totalGold)
		time.Sleep(250 * time.Millisecond)
	}

	return totalGold
}

func findOptimalRoute() {
	possibleRoutes := [][]rune{
		{'A', 'B', 'D'},
		{'A', 'C', 'D'},
		{'A', 'B', 'C', 'D'},
		{'A', 'C', 'B', 'D'},
	}

	maxGold := 0
	var optimalRoute []rune

	for _, route := range possibleRoutes {
		gold := traverseMaze(route, 40)
		fmt.Printf("\nRoute %s finished with %d gold\n", string(route), gold)
		time.Sleep(250 * time.Millisecond)
		if gold > maxGold {
			maxGold = gold
			optimalRoute = route
		}
	}

	fmt.Printf("\nOptimal route: %s\n", string(optimalRoute))
	fmt.Printf("Maximum gold: %d\n", maxGold)
}

func min(a, b rune) rune {
	if a < b {
		return a
	}
	return b
}

func max(a, b rune) rune {
	if a > b {
		return a
	}
	return b
}

func main() {
	findOptimalRoute()
}