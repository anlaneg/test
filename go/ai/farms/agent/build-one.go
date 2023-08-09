package agent

import (
	"github.com/anlaneg/frame/frame"
	"fmt"
)

/*这种agnet保在保护区建一个frame*/
type BuildOneAgent struct {
	frame.Agent
}

func (one *BuildOneAgent) GetRequest() *frame.Request {
	//坐标【1，1】
	//index := (1*frame.GAMEMAP_MAX_ROWS) + 1
	//坐标[0,0]
	index := 0
	row := index % frame.GAMEMAP_MAX_ROWS
	column := index / frame.GAMEMAP_MAX_ROWS
	fmt.Println(frame.AgentWhatAt(one,row,column))
	if frame.AgentWhatAt(one,row,column) == frame.PlaceType_none {
		//发现有空闲
		return &frame.Request{Name:frame.PlaceType_garden,Row:row,Column:column}
	}
	return nil
}

func (one *BuildOneAgent) GetMagic() interface{} {
	return nil
}