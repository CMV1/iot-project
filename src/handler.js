// token-manager.js
const { google } = require('googleapis');
const fs = require('fs');

const credentials = require('./credentials.json');

const oauth2Client = new google.auth.OAuth2(
  credentials.installed.client_id,       
  credentials.installed.client_secret,    
  credentials.installed.redirect_uris[0]  
);

// First time: Get auth URL
function getAuthUrl() {
  const url = oauth2Client.generateAuthUrl({
    access_type: 'offline',
    scope: ['https://www.googleapis.com/auth/calendar.readonly']
  });
  console.log('Visit this URL:', url);
}

// Second time: Exchange code for tokens
async function getToken(code) {
  const { tokens } = await oauth2Client.getToken(code);
  fs.writeFileSync('tokens.json', JSON.stringify(tokens));
  console.log('Access Token:', tokens.access_token);
  console.log('Refresh Token:', tokens.refresh_token);
}

// Use saved tokens
function loadTokens() {
  const tokens = JSON.parse(fs.readFileSync('tokens.json'));
  console.log('Access Token:', tokens.access_token);
  return tokens.access_token;
}

// Run this
//getAuthUrl();
getToken('https://accounts.google.com&code=4/0AeoWuM8UgW08TEv_nC2bhMJPvl3gfycKhv_kwWKfGTBOyFzL7Xbho9ozFTKlimyZqc6mAQ&scope=https://www.googleapis.com/auth/calendar.readonly');
//loadTokens();
