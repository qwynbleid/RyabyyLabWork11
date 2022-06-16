#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include "libpq-fe.h"

int main(int argc, char **argv) {
        const char *conninfo;
        PGconn     *conn;
        PGresult   *res;
        PGnotify   *notify;
        char db_name[] = "ryabij_andrij";

        conn = PQsetdbLogin(NULL,NULL,NULL,NULL,db_name,NULL,NULL);
        if (PQstatus(conn) != CONNECTION_OK) {
                fprintf(stderr, "Connection failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
        }

        res = PQexec(conn, "NOTIFY ryabij");
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
                fprintf(stderr, "Sh*t! NOTIFY failed: %s", PQerrorMessage(conn));
                PQclear(res);
                PQfinish(conn);
                exit(1);
        }
        PQclear(res);
        PQfinish(conn);
        return 0;
}
