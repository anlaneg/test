package frame

type Item struct {
	cost                int
	clearCost           int
	baseIncome          float64
	emptyFactor         float64
	sameTypeFactor      float64
	differentTypeFactor float64
	riverFactor         float64
}

var (
	wheat = &Item{
		cost:                1,
		clearCost:           2,
		emptyFactor:         1,
		sameTypeFactor:      1.5,
		differentTypeFactor: 1.2,
		riverFactor:         3.9,
		baseIncome:          10,
	}

	garden = &Item{
		cost:                1,
		clearCost:           2,
		emptyFactor:         1.4,
		sameTypeFactor:      0.7,
		differentTypeFactor: 0.7,
		riverFactor:         5.9,
		baseIncome:          10,
	}

	patch = &Item{
		cost:                1,
		clearCost:           2,
		emptyFactor:         1,
		sameTypeFactor:      1.2,
		differentTypeFactor: 1.6,
		riverFactor:         4.7,
		baseIncome:          10,
	}

	river_cost int = 1

	river_poison_mist_recover_factor float64 = 0.3

	farms = map[PlaceType]*Item{
		PlaceType_patch:  patch,
		PlaceType_garden: garden,
		PlaceType_wheat:  wheat,
	}
)

func FarmsGetBaseIncome(placeType PlaceType) float64 {
	v, ok := farms[placeType]
	if !ok {
		panic("!ok")
	}

	return v.baseIncome
}

func FarmsGetEmptyFactor(placeType PlaceType) float64 {
	v, ok := farms[placeType]
	if !ok {
		panic("!ok")
	}

	return v.emptyFactor
}

func FarmsGetSameTypeFactor(placeType PlaceType) float64 {
	v, ok := farms[placeType]
	if !ok {
		panic("!ok")
	}

	return v.sameTypeFactor
}

func FarmsGetDifferentTypeFactor(placeType PlaceType) float64 {
	v, ok := farms[placeType]
	if !ok {
		panic("!ok")
	}

	return v.differentTypeFactor
}

func FarmsGetRiverFactor(placeType PlaceType) float64 {
	v, ok := farms[placeType]
	if !ok {
		panic("!ok")
	}

	return v.riverFactor
}

func FarmsGetPoisonMistRecoverFactor() float64 {
	return river_poison_mist_recover_factor
}
