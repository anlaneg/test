package frame

type Request struct {
	Name   PlaceType
	Row    int
	Column int
}

func (request *Request) IsClearing() bool {
	if PlaceType_none == request.Name {
		return true
	} else {
		return false
	}
}

type AgentMethod interface {
	GetRequest() *Request
	GetMagic() interface{}
	GetName() string
	SetName(string)
	Init()
	GetPlayerID() PlayerID
	setPlayerID(id PlayerID)
}

type Agent struct {
	name string
	id   PlayerID
	AgentMethod
}

func (agent *Agent) GetName() string {
	return agent.name
}

func (agent *Agent) SetName(n string) {
	agent.name = n
}

func (agent *Agent) setPlayerID(id PlayerID) {
	agent.id = id
}

func (agent *Agent) GetPlayerID() PlayerID {
	return agent.id
}

func (agent *Agent) Init() {

}

func AgentWhatAt(self AgentMethod, row int, column int) PlaceType {
	if self == nil {
		panic("self == nil")
	}
	aiIdx := self.GetPlayerID().getPlayerIndex()
	row,column = game_global.players[aiIdx].MapPlace(row, column)
	return game_global.gameMap.GetPlaceType(row, column)
}
