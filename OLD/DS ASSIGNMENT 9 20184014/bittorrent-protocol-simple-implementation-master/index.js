// Purva Gautam
// 20184014
'use strict';

const torrentParser = require('./src/torrent-parser');
const handleTorrent = require('./src/handle-torrent');

const torrent = torrentParser.open('./test/test2.torrent');

handleTorrent(torrent, torrent.info.name);
