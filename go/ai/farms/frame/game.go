package frame

import (
	"fmt"
)

type Game struct {
	duration                int
	workerSpeed             int
	mistSameTypeFactor      float64
	mistDifferentTypeFactor float64
	mistPoisonFactor        float64
	gameMap                 GameMap
	players                 [2]*Player
}

var (
	//定义全局变量game
	game_global = &Game{}
)

/*func (game *Game) GetItemName(row int, column int) (*ItemName, int) {
	item0 := game.agent[0].agentMap.v[row][column]
	item1 := game.agent[1].agentMap.v[row][column]

	if !item0.Valid() {
		panic("!item0.Valid()")
	}

	if !item1.Valid() {
		panic("!item1.Valid()")
	}

	if item0.isNone() {
		if !item1.isNone() {
			return &ItemName{name: item1.name}, 1
		} else {
			return &ItemName{name: "none"}, -1
		}
	} else {
		if !item1.isNone() {
			panic("!item1.isNone()")
		}
		return &ItemName{name: item0.name}, 0
	}
}*/

/*func (game *Game) Valid(itemName *ItemName, row int, column int) bool {
	if !itemName.Valid() {
		return false
	}

	return game.IsNone(row, column)
}*/

/*func (game *Game) IsNone(row int, column int) bool {
noneItem, _ := game.GetItemName(row, column)
	if !noneItem.isNone() {
		return false
	}

	return true
}*/

func (game *Game) GetOpponent(player *Player) *Player {
	return game.players[player.id.getOpponent().getPlayerIndex()]
}

func (game *Game) GetDuration() int{
	return game.duration
}

func (game *Game) Init(player1 *Player, player2 *Player) {
	player1.id = PlayerID_1
	player1.ai.setPlayerID(player1.id)
	player2.id = PlayerID_2
	player2.ai.setPlayerID(player2.id)

	game.duration = 120
	game.workerSpeed = 12
	game.mistSameTypeFactor = 2
	game.mistDifferentTypeFactor = 0.5
	game.mistPoisonFactor = 0

	game.players[player1.id.getPlayerIndex()] = player1
	game.players[player2.id.getPlayerIndex()] = player2
	for i := 0; i < 2; i = i + 1 {
		game.players[i].earn = 0
	}

	for row := 0; row < GAMEMAP_MAX_ROWS; row = row + 1 {
		for column := 0; column < GAMEMAP_MAX_COLUMNS; column = column + 1 {
			game.gameMap.v[row][column] = &ItemName{name: PlaceType_none, playerIndex: -1}
		}
	}
}

func Init(player1 *Player, player2 *Player) *Game {
	game_global.Init(player1,player2)
	return game_global
}

func Power(base float64, cnt int) float64 {
	var result float64 = 1
	for i := 0; i < cnt; i++ {
		result = result * base
	}

	return result
}

func (game *Game) GameGetmistPoisonFactor() float64 {
	return game.mistPoisonFactor
}

func (game *Game) GameGetMistSameTypeFactor() float64 {
	return game.mistSameTypeFactor
}

func (game *Game) GameGetMistDifferentTypeFactor() float64 {
	return game.mistDifferentTypeFactor
}

func (game *Game) GetFarmsEarn(player *Player, currentId int, palceType PlaceType, row int, column int) float64 {
	var earn float64
	baseIncome := FarmsGetBaseIncome(palceType)

	//如果农场旁边有一个空的地块，农场收入会被乘以这个数
	emptyFactor := FarmsGetEmptyFactor(palceType)
	cnt := game.gameMap.NearEmptyCount(row, column)
	earn = baseIncome * Power(emptyFactor, cnt)

	//如果农场旁边有一个相同类型的农场，农场收入会被乘以这个数
	sameTypeFactor := FarmsGetSameTypeFactor(palceType)
	cnt = game.gameMap.NearSameTypeCount(palceType, row, column)
	earn = earn * Power(sameTypeFactor, cnt)

	//如果农场旁边有一个不相同类型的农场，农场收入会被乘以这个数
	differentTypeFactor := FarmsGetDifferentTypeFactor(palceType)
	cnt = game.gameMap.NearDifferentTypeCount(palceType, row, column)
	earn = earn * Power(differentTypeFactor, cnt)

	//如果农场旁边有一个满河，农场收入会被乘以这个数（即使农场旁边有多个满河，也只适用于一次)
	riverFactor := FarmsGetRiverFactor(palceType)
	fullRiverCnt := game.gameMap.NearFullRiverCount(row, column)
	//雨水给予农场部分效果，就如同它们旁边有一个完整的满河单元
	//（如果农场旁边已有满河，则雨水效果已覆盖，不再有额外效果）
	if fullRiverCnt > 0 || (fullRiverCnt == 0 && game.HasRainAttack(currentId, row, column)) {
		earn = earn * riverFactor
	}

	//XXX 河流会增加riverIncome参数，但缺少必要信息，这里忽略。

	// 毒气攻击，则乘以mistPoisonFactor
	if game.HasPoisonAttack(currentId, row, column) {
		//雨水还会清除所有被雨水淋湿区域的雾气
		if !game.HasRainAttack(currentId, row, column) {
			mistPoisonFactor := game.GameGetmistPoisonFactor()
			//如果一个靠近充满水的河流的农场上有毒气，那么返还一部分收入
			if fullRiverCnt != 0 {
				poisonMistRecoverFactor := FarmsGetPoisonMistRecoverFactor()
				drop := earn - (earn * mistPoisonFactor)
				earn = drop * poisonMistRecoverFactor
			} else {
				earn = earn * mistPoisonFactor
			}
		}
	}

	// 雾气攻击，如果类型相同，则乘以mistSameTypeFactor，否则乘以mistDifferentTypeFactor
	attack, mistType := game.HasMistAttack(currentId, row, column)
	if attack {
		//雨水还会清除所有被雨水淋湿区域的雾气
		if !game.HasRainAttack(currentId, row, column) {
			if mistType == PlaceType_patch {
				mistSameTypeFactor := game.GameGetMistSameTypeFactor()
				earn = earn * mistSameTypeFactor
			} else {
				mistDifferentTypeFactor := game.GameGetMistDifferentTypeFactor()
				earn = earn * mistDifferentTypeFactor
			}
		}
	}

	//XXX 雨水还会减慢机器人的移动速度，但机器人移动速度缺少单位信息，这里忽略
	//XXX 雨水可使干河有riverBonusFactor,但缺少关于此Factor的应用说明，这里忽略。
	return earn
}

func (game *Game) GetRiverEarn(player *Player, row int, column int) float64 {
	//河流没有收入
	return 0
}

func (game *Game) UpdateEarn(player *Player, currentId int) {
	for row := 0; row < GAMEMAP_MAX_ROWS; row = row + 1 {
		for column := 0; column < GAMEMAP_MAX_COLUMNS; column = column + 1 {
			item := game.gameMap.v[row][column]
			if item.playerIndex == player.id.getPlayerIndex() {
				switch item.name {
				case PlaceType_patch, PlaceType_garden, PlaceType_wheat:
					player.earn += game.GetFarmsEarn(player, currentId, item.name, row, column)
					break
				case PlaceType_river:
					player.earn += game.GetRiverEarn(player, row, column)
					break
				default:
					panic("item.name == PlaceType_none")
					break
				}
			}
		}
	}
}

func (game *Game) UpdateRequest(ai *Player, currentId int) {
	request := ai.GetRequest()
	if request == nil {
		/*容许agent不返回request*/
		return
	}
	
	if request.IsClearing() {
		if game.gameMap.IsNone(request.Row, request.Column) {
			panic("game.gameMap.IsNone(request.row, request.column)")
		}

		/*不容许清除river*/
		if game.gameMap.isRiver(request.Row, request.Column) {
			panic(game.gameMap.isRiver(request.Row, request.Column))
		}

		if ai.IsProtect(request.Row, request.Column) {
			panic("game.IsProtect(ai.opponentId,request.row, request.column)")
		}

		game.gameMap.SetNone(request.Row, request.Column)
		return
	}

	if ai.IsProtect(request.Row, request.Column) {
		panic("ai.IsProtect(request.row, request.column)")
	}
	
	if !game.gameMap.IsNone(request.Row, request.Column) {
		panic("!game.gameMap.IsNone(request.Row, request.Column)")
	}

	fmt.Printf("[%s] build %s at [%2d,%2d]\n", ai.GetPlayerName(), request.Name, request.Row, request.Column)
	game.gameMap.SetItemName(ai, request.Row, request.Column, request.Name)
}

func (game *Game) UpdateMagic(ai *Player,currentId int) {
	ai.UpdateMagic(currentId)
}

func (game *Game) HasPoisonAttack(seq int, row int, column int) bool {
	//毒雾攻击必须两个玩家都有使用魔法
	if game.players[0].magicState != nil && game.players[1].magicState != nil &&
		game.players[0].magicState.end >= seq && game.players[1].magicState.end >= seq {
		player0_mist, ok0 := game.players[0].magicState.magic.(*Mist)
		player1_mist, ok1 := game.players[1].magicState.magic.(*Mist)
		if ok0 && ok1 && (player0_mist.farmType != player1_mist.farmType) {
			/*两个玩家都使用雾魔法且针对的农场类型不同*/
			offset := player0_mist.row - player1_mist.row
			if offset >= -2 && offset <= 2 {
				//此时确定有毒雾攻击，接下来检查当前行是否在毒雾范围内
				switch offset {
				case -2:
					//此时毒雾行有一行，为 player0_mist.row + 1
					if row == (player0_mist.row + 1) {
						return true
					}
					break
				case -1, 1:
					//此时毒雾行有二行，为player0_mist.row,player1_mist.row
					if row == player0_mist.row || row == player1_mist.row {
						return true
					}
					break
				case 0:
					//此时毒雾行有三行，为player0_mist.row-1，player0_mist.row,player0_mist.row+1
					if row == (player0_mist.row-1) || row == player0_mist.row || row == (player0_mist.row+1) {
						return true
					}
					break
				case 2:
					//此时毒雾行有一行，为 player0_mist.row - 1
					if row == (player0_mist.row - 1) {
						return true
					}
					break
				}
			}
		}
	}
	return false
}

func (game *Game) HasRainAttack(seq int, row int, column int) bool {
	if game.players[0].magicState != nil {
		player0_rain, ok := game.players[0].magicState.magic.(*Rain)
		if ok && game.players[0].magicState.end >= seq && player0_rain.Column-1 <= column && player0_rain.Column+1 >= column {
			//fmt.Printf("time %d,[%d,%d] %s rain\n", seq,row,column,game.players[0].ai.GetName())
			return true
		}
	}

	if game.players[1].magicState != nil {
		player1_rain, ok := game.players[1].magicState.magic.(*Rain)
		if ok && game.players[1].magicState.end >= seq && player1_rain.Column-1 <= column && player1_rain.Column+1 >= column {
			//fmt.Printf("time %d,[%d,%d] %s rain\n", seq,row,column,game.players[1].ai.GetName())
			return true
		}
	}

	return false
}

func (game *Game) HasMistAttack(seq int, row int, column int) (bool, PlaceType) {
	/*首先必须排除毒雾攻击*/
	if game.HasPoisonAttack(seq, row, column) {
		return false, PlaceType_none
	}

	if game.players[0].magicState != nil {
		player0_mist, ok := game.players[0].magicState.magic.(*Mist)
		if ok && game.players[0].magicState.end >= seq && player0_mist.row-1 <= row && player0_mist.row+1 >= row {
			return true, player0_mist.farmType
		}
	}

	if game.players[1].magicState != nil {
		player1_mist, ok := game.players[1].magicState.magic.(*Mist)
		if ok && game.players[1].magicState.end >= seq && player1_mist.row-1 <= row && player1_mist.row+1 >= row {
			return true, player1_mist.farmType
		}
	}

	return false, PlaceType_none
}
