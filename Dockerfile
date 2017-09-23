FROM alpine:3.5

# install dependencies
RUN apk update
RUN apk add git python3 python3-dev make g++

RUN python3.5 -m ensurepip
RUN pip3 install flask

# clone the repo
RUN echo "Cloning repo 1"
RUN git clone https://github.com/nevinlazarus/potential-potato.git

# cd potential-potato
WORKDIR "potential-potato"
RUN make
RUN chmod +x main.py

# Add for debugging container
#ENTRYPOINT ["sh"]

ENTRYPOINT ["python3.5", "main.py"]
