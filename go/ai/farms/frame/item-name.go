package frame

type PlaceType string

const (
	PlaceType_patch  PlaceType = "patch"
	PlaceType_garden PlaceType = "garden"
	PlaceType_wheat  PlaceType = "wheat"
	PlaceType_river  PlaceType = "river"
	PlaceType_none   PlaceType = "none"
)

type ItemName struct {
	name        PlaceType
	playerIndex int
}

/*func (itemName *ItemName) Valid() bool {
	switch itemName.name {
	case "patch", "garden", "wheat", "river":
		return true
		case "none":
		return true
	default:
		return false
	}
}*/

func (itemName *ItemName) IsNone() bool {
	if itemName.name == PlaceType_none {
		return true
	}
	return false
}

/*
func (itemName *ItemName) IsPatch() bool {
	if itemName.name == "patch" {
		return true
	}
	return false
}

func (itemName *ItemName) IsGarden() bool {
	if itemName.name == "garden" {
		return true
	}
	return false
}

func (itemName *ItemName) IsWheat() bool {
	if itemName.name == "wheat" {
		return true
	}
	return false
}
*/

func (itemName *ItemName) IsRiver() bool {
	if itemName.name == PlaceType_river {
		return true
	}
	return false
}
