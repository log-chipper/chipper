package chipper

import (
	"fmt"
	"net"
)

type Client struct {
	conn *net.UnixConn
	service string
	source string
}

func NewClient(socketPath, service, source string) (*Client, error) {
	addr := &net.UnixAddr{Name: socketPath, Net: "unixgram"}
	conn, err := net.DialUnix("unixgram", nil, addr)
	if err != nil {
		return nil, err
	}

	return &Client{
		conn: conn,
		service: service,
		source: source,

	}, nil
}

func (c *Client) Log(level, msg string) error {
	line := fmt.Sprintf(
		"level=%s service=%s source=%s msg=\"%s\"",
		level, c.service, c.source, msg,
	)
	_, err := c.conn.Write([]byte(line))
	return err
}

func (c *Client) Close() error {
	return c.conn.Close()
}
