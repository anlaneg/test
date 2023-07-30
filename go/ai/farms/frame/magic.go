package frame

type Magic struct {
}

type Mist struct {
	Magic
	farmType PlaceType
	row      int
}

type Rain struct {
	Magic
	Column int
}

type MagicState struct {
	magic    interface{}
	start    int
	end      int
	cooldown int
}

func magicGetMistCooldown(placeType PlaceType) int {
	switch placeType {

	case PlaceType_wheat:
		return 6
	case PlaceType_garden:
		return 6
	case PlaceType_patch:
		return 6
	default:
		panic("placeType error")
	}
}

func magicGetMistDuration(placeType PlaceType) int {
	switch placeType {

	case PlaceType_wheat:
		return 5
	case PlaceType_garden:
		return 5
	case PlaceType_patch:
		return 5
	default:
		panic("placeType error")
	}
}

func magicGetRainCooldown() int {
	return 12
}

func magicGetRainDuration() int {
	return 5
}
