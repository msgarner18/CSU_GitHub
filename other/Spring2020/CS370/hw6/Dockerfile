FROM node:14

WORKDIR /

COPY package.json /

RUN npm install express /

COPY . .

CMD ["npm", "start"]