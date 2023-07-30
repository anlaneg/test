package agent

import (
	"github.com/anlaneg/frame/frame"
)

/*这种agnet啥也不干，得分为0*/
type NULLAgent struct {
	//name string
	frame.Agent
	//frame.AgentMethod
}

func (null *NULLAgent) GetRequest() *frame.Request {
	return nil
}

func (null *NULLAgent) Init() {
}

func (null *NULLAgent) GetMagic() interface{} {
	return nil
}