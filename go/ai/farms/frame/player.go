package frame
import (
	"fmt"
)

type PlayerID int32

const (
	PlayerID_1 PlayerID = 1
	PlayerID_2 PlayerID = 2
)

func (id PlayerID) getOpponent() PlayerID {
	if id == PlayerID_1 {
		return PlayerID_2
	} else {
		return PlayerID_1
	}
}

func (id PlayerID) getPlayerIndex() int {
	if id == PlayerID_1 {
		return 0
	} else {
		return 1
	}
}

type Player struct {
	ai         AgentMethod
	id         PlayerID
	earn       float64
	magicState *MagicState
}

func NewPlayer(agent AgentMethod) *Player {
	return &Player{ai: agent}
}

/*func (player *Player) GetOpponent() PlayerID {
	if player.id != PlayerID_1 && player.id != PlayerID_2 {
		panic("player.id != PlayerID_1 && player.id != PlayerID_2")
	}

	if player.id == PlayerID_1 {
		return PlayerID_2
	} else {
		return PlayerID_1
	}
	return player.id.getOpponent()
}*/

func (player *Player) GetPlayerName() string{
	return player.ai.GetName()
}

func (player *Player) GetPlayerEarn() float64{
	return player.earn
}

func (player *Player) MapPlace(row int, column int) (int, int) {
	if row < 0 || row >= GAMEMAP_MAX_ROWS || column < 0 || column >= GAMEMAP_MAX_COLUMNS {
		panic("row < 0 || row >= GAMEMAP_MAX_ROWS || column < 0 || column >= GAMEMAP_MAX_COLUMNS")
	}

	if player.id == PlayerID_1 {
		return row, column
	} else {
		return (GAMEMAP_MAX_ROWS - 1) - row, (GAMEMAP_MAX_COLUMNS - 1) - column
	}
}

func (player *Player) GetRequest() *Request {
	request := player.ai.GetRequest()
	if request != nil {
		request.Row, request.Column = player.MapPlace(request.Row, request.Column)
	}
	return request
}

func (player *Player) getMagic(seq int) {
	magic := player.ai.GetMagic()
	if magic == nil {
		return
	}

	mist, ok := magic.(Mist)
	if ok {
		mist.row, _ = player.MapPlace(mist.row, 0)
		end_seq := seq + magicGetMistDuration(mist.farmType)
		end_cooldown := seq + magicGetMistCooldown(mist.farmType)
		player.magicState = &MagicState{magic: mist, start: seq, end: end_seq, cooldown: end_cooldown}
		fmt.Printf("[%s] mist(%s) at [%d,*] time [%d,%d] cooldown %d\n", player.ai.GetName(),mist.farmType,mist.row,seq,end_seq,end_cooldown)
		return
	}

	rain, ok := magic.(*Rain)
	if ok {
		_, rain.Column = player.MapPlace(0, rain.Column)
		end_seq := seq + magicGetRainDuration()
		end_cooldown := seq + magicGetRainCooldown()
		player.magicState = &MagicState{magic: rain, start: seq, end: end_seq, cooldown: end_cooldown}
		fmt.Printf("[%s] rain at [*,%d] time [%03d,%03d] cooldown %d\n", player.ai.GetName(),rain.Column,seq,end_seq,end_cooldown)
		return
	} else {
		panic("magic error")
	}
}

func (player *Player) UpdateMagic(seq int) {
	if player.magicState == nil {
		player.getMagic(seq)
		return
	}

	// 这里将cooldown实现为：一次只能使用一种魔法，魔法cooldown未结束前不得使用其它魔法
	if player.magicState.cooldown <= seq {
		player.magicState = nil
		player.getMagic(seq)
	}
}

func (player *Player) IsProtect(row int, column int) bool {
	/*此函数调用时，认为row,column已依据MapPlace进行了转换*/
	if player.id == PlayerID_1 {
		//对player1来说，地图右侧三列的区域是加了保护的
		if column >= GAMEMAP_MAX_COLUMNS-GAMEMAP_MAX_PROTECT_COLUMNS && column < GAMEMAP_MAX_COLUMNS {
			return true
		}
	} else {
		//对player2来说，地图左侧三列的区域是加了保护的
		if column >= 0 && column < GAMEMAP_MAX_PROTECT_COLUMNS {
			return true
		}
	}
	return false
}
