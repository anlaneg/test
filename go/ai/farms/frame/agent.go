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
}

/*type Agent struct {
	Name string
	AgentMethod
}*/
