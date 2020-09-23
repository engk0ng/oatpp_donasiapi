FROM qsapibase:latest

WORKDIR /usr/src/qsaspi/donasi-api
COPY . .
RUN cmake .
RUN make
EXPOSE 8787 8787
CMD ./donasi-api-exe