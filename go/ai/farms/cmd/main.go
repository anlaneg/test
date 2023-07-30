package main

import (
	"fmt"
	"github.com/anlaneg/frame/agent"
	"github.com/anlaneg/frame/frame"
)

/*type RequestType string

const (
	RequestType_clear  RequestType = "clear"
	RequestType_patch  RequestType = "patch"
	RequestType_garden RequestType = "garden"
	RequestType_wheat  RequestType = "wheat"
	RequestType_river  RequestType = "river"
)*/

func main() {

	game := &frame.Game{}

	agent1 := &agent.BuildProtectRainMaigcAgent{}
	agent1.Init()
	agent1.SetName("robot1")
	agent2 := &agent.BuildProtectOnlyAgent{}
	agent2.Init()
	agent2.SetName("robot2")
	
	player1 := frame.NewPlayer(agent1)
	player2 := frame.NewPlayer(agent2)

	game.Init(player1, player2)
	fmt.Println(game.GetDuration())
	for i := 0; i <= game.GetDuration(); i = i + 1 {
		fmt.Printf("[%03d]%s: %f\n", i, player1.GetPlayerName(), player1.GetPlayerEarn())
		fmt.Printf("[%03d]%s: %f\n", i, player2.GetPlayerName(), player2.GetPlayerEarn())

		game.UpdateEarn(player1, i)
		game.UpdateEarn(player2, i)

		game.UpdateRequest(player1, i)
		game.UpdateRequest(player2, i)

		game.UpdateMagic(player1, i)
		game.UpdateMagic(player2, i)
	}
}
