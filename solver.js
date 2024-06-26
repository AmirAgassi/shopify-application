const costs = {
    'AB': 2 + 3 * 4 - 5 / 10 + 5**2,
    'AC': 2**3 + 4 * 5 - 6 /10 + 1,
    'BC': 5 * 4 - 2 + 5**2 - 7,
    'BD': 3 + 4 * 5 - 8 / 2 + 1,
    'CD': 3**3 + 8 - 5 * 3 + 8
};

const roomGold = { 'A': 40, 'B': 50, 'C': 75, 'D': 100 };

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function traverseMaze(route, gold) {
    let totalGold = gold;

    console.log(`\nTrying route: ${route.join(' -> ')}`);
    console.log(`Starting gold: ${totalGold}`);
    await sleep(250);

    for (let i = 0; i < route.length - 1; i++) {
        const currentRoom = route[i];
        const nextRoom = route[i + 1];
        const path = [currentRoom, nextRoom].sort().join('');
        const pathCost = Math.ceil(costs[path]);

        console.log(`\nMoving from ${currentRoom} to ${nextRoom}. Path cost: ${pathCost}`);
        await sleep(250);

        if (totalGold < pathCost) {
            console.log("Not enough gold to proceed!");
            await sleep(250);
            return 0;
        }

        totalGold -= pathCost;
        console.log(`Paid ${pathCost} gold. Remaining gold: ${totalGold}`);
        await sleep(250);

        totalGold += roomGold[nextRoom];
        console.log(`Collected ${roomGold[nextRoom]} gold from room ${nextRoom}. New total: ${totalGold}`);
        await sleep(250);
    }

    return totalGold;
}

async function findOptimalRoute() {
    const possibleRoutes = [
        ['A', 'B', 'D'],
        ['A', 'C', 'D'],
        ['A', 'B', 'C', 'D'],
        ['A', 'C', 'B', 'D']
    ];

    let maxGold = 0;
    let optimalRoute = [];

    for (const route of possibleRoutes) {
        const gold = await traverseMaze(route, 40);
        console.log(`\nRoute ${route.join(' -> ')} finished with ${gold} gold`);
        await sleep(250);
        if (gold > maxGold) {
            maxGold = gold;
            optimalRoute = route;
        }
    }

    console.log(`\nOptimal route: ${optimalRoute.join('')}`);
    console.log(`Maximum gold: ${maxGold}`);
}

findOptimalRoute();