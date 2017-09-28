from ubuntu:16.04
MAINTAINER Malcolm Davis <me@malcolmdavis.xyz>
# Ubuntu Docker mods
ARG DEBIAN_FRONTEND=noninteractive
# Dependencies
RUN dpkg --add-architecture i386 && apt-get update \
    && apt-get install -y expect wget  \
    libc6-i386 lib32stdc++6 lib32gcc1 lib32ncurses5 lib32z1
RUN apt-get install -y curl
RUN apt-get install -y build-essential libssl-dev
RUN apt-get install -y git
#NVM
RUN curl https://raw.githubusercontent.com/creationix/nvm/v0.33.4/install.sh | bash
RUN /bin/bash -c "source ~/.profile"
# Nodejs
RUN curl -sL https://deb.nodesource.com/setup_6.x -o nodesource_setup.sh \
	&& chmod +x nodesource_setup.sh \
	&&  ./nodesource_setup.sh \
	&& rm nodesource_setup.sh
RUN apt-get update \
    && apt-get install -y nodejs
#Loopback
RUN npm install -g strongloop
RUN mkdir /tmp/espe
RUN cd /tmp/espe && git clone https://github.com/mrholek/CoreUI-AngularJS.git
WORKDIR /tmp/espe

