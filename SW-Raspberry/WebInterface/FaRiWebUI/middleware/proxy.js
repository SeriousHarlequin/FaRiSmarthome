import { createProxyMiddleware } from 'http-proxy-middleware';

export default createProxyMiddleware('/fetchTemp', {
  target: 'http://192.168.143.28',
  changeOrigin: true,
});