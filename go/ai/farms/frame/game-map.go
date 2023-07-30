package frame

const (
	//AGENT_NUMBERS = 2
	GAMEMAP_MAX_ROWS    = 10
	GAMEMAP_MAX_COLUMNS = 12
	GAMEMAP_MAX_PROTECT_COLUMNS = 3
)

type GameMap struct {
	v [GAMEMAP_MAX_ROWS][GAMEMAP_MAX_COLUMNS]*ItemName
}

func (gameMap *GameMap) checkIndex(row int, column int) bool {
	if row < 0 || row >= GAMEMAP_MAX_ROWS {
		return false
	}

	if column < 0 || column >= GAMEMAP_MAX_COLUMNS {
		return false
	}
	return true
}

func (gameMap *GameMap) nearCount(row int, column int, match func(*ItemName) bool) int {
	cnt := 0
	/*这里定义的旁边仅包括4个正方向，不含斜方向*/
	//（0,-1),(0,+1),(1，0),(-1，0)
	/*这个表述用go处理太难受了。。。。*/
	map_near := []struct {
		x int
		y int
	}{
		{x: 0, y: -1},
		{x: 0, y: 1},
		{x: 1, y: 0},
		{x: -1, y: 0},
	}

	for _, elem := range map_near {
		row_offset, column_offset := elem.x, elem.y
		if !gameMap.checkIndex(row+row_offset, column+column_offset) {
			continue
		}

		if match(gameMap.v[row+row_offset][column+column_offset]) {
			cnt++
		}
	}
	return cnt
}

func (gameMap *GameMap) NearEmptyCount(row int, column int) int {
	return gameMap.nearCount(row, column, func(item *ItemName) bool {
		if item.name == PlaceType_none {
			return true
		}
		return false
	})
}

func (gameMap *GameMap) NearSameTypeCount(palceType PlaceType, row int, column int) int {
	return gameMap.nearCount(row, column, func(item *ItemName) bool {
		if item.name == palceType {
			return true
		}
		return false
	})
}

func (gameMap *GameMap) NearDifferentTypeCount(palceType PlaceType, row int, column int) int {
	return gameMap.nearCount(row, column, func(item *ItemName) bool {
		if item.name == palceType && item.name != PlaceType_none {
			return true
		}
		return false
	})
}

func (gameMap *GameMap) NearFullRiverCount(row int, column int) int {
	return gameMap.nearCount(row, column, func(item *ItemName) bool {
		if item.name == PlaceType_river {
			//TODO 这里不能简单的返回true,需要检查从这里出发，能否到达上下边界，以确保是满河。
			//也可借助driver不能被移除的特性，在item上加标记来判断。这里先简单返回true
			return true
		}
		return false
	})
}

func (gameMap *GameMap) IsNone(row int, column int) bool {
	if !gameMap.checkIndex(row, column) {
		panic("!gameMap.checkIndex(row, column)")
	}

	return gameMap.v[row][column].IsNone()
}

func (gameMap *GameMap) isRiver(row int, column int) bool {
	if !gameMap.checkIndex(row, column) {
		panic("!gameMap.checkIndex(row, column)")
	}

	return gameMap.v[row][column].IsRiver()
}

func (gameMap *GameMap) GetPlaceType(row int, column int) PlaceType {
		if !gameMap.checkIndex(row, column) {
		panic("!gameMap.checkIndex(row, column)")
	}

	return gameMap.v[row][column].name
}

func (gameMap *GameMap) _setItemName(player int, row int, column int, placeType PlaceType) {
	if !gameMap.checkIndex(row, column) {
		panic("!gameMap.checkIndex(row, column)")
	}

	gameMap.v[row][column] = &ItemName{name: placeType, playerIndex: player}
}

func (gameMap *GameMap) SetNone(row int, column int) {
	gameMap._setItemName(-1, row, column, PlaceType_none)
}

func (gameMap *GameMap) SetItemName(player *Player, row int, column int, placeType PlaceType) {
	gameMap._setItemName(player.id.getPlayerIndex(), row, column, placeType)
}
