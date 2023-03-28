FROM node:current-alpine3.17

WORKDIR /usr/src/app
COPY package*.json ./
RUN npm install

# Bundle app source
COPY . .
EXPOSE 3000
CMD [ "node", "main.js" ]
