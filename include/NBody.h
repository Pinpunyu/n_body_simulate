#ifndef _NBody_H_
#define _NBody_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
// #include <cuda.h>
#include "VecAlg.h"
#include "Picture.h"

void n_body_simulate_cpu(char* fileName, int show_flag);
void n_body_simulate_gpu(char* fileName, int show_flag);
void init_system(char* fileName);
void resolve_collision(int cur_cycle);
void compute(int cur_cycle);
void print_variable(int cycle);

// __global__ void compute_gpu(int cur_cycle);

int bodies, cycles;
double *masses, GravConstant;
vector **pos, **vel, **acc;

void n_body_simulate_cpu(char* fileName, int show_flag){
    /*  main simulate */
    init_system(fileName);
    printf("Body   :     x          y          z        |     vx          vy          vz   ");

    for(int i=0; i<cycles; i++){
        compute(i);
        resolve_collision(i);
        print_variable(i);
    }

    if(show_flag == 1){
		show_simulate(pos, cycles, bodies);
        printf("show simulate\n");
    }
}

void init_system(char* fileName){
    /*  initialize */
    FILE* fp = fopen(fileName, "r");
    
    fscanf(fp, "%lf%d%d", &GravConstant, &bodies, &cycles);

    /* 質量masses 位置pos 速度vel 加速度acc */
    masses = (double*)malloc(bodies * sizeof(double));
    pos = (vector**)malloc(cycles * sizeof(vector*));
    vel = (vector**)malloc(cycles * sizeof(vector*));
    acc = (vector**)malloc(cycles * sizeof(vector*));

    for(int i = 0; i < cycles; i++){
        pos[i] = (vector*)malloc(bodies * sizeof(vector));
        vel[i] = (vector*)malloc(bodies * sizeof(vector));
        acc[i] = (vector*)malloc(bodies * sizeof(vector));
    }

    for(int i = 0; i < bodies; i++){
        fscanf(fp, "%lf", &masses[i]);
        fscanf(fp, "%lf%lf%lf", &pos[0][i].x, &pos[0][i].y, &pos[0][i].z);
        fscanf(fp, "%lf%lf%lf", &vel[0][i].x, &vel[0][i].y, &vel[0][i].z);
    }
    
    fclose(fp);
}

void compute(int cur_cycle){
    /*  compute accelerations       */
    /*  ai = (G * mj / Rij^3) * Rij */

    for(int i = 0; i < bodies; i++){
        acc[cur_cycle][i].x = 0;
        acc[cur_cycle][i].y = 0;
        acc[cur_cycle][i].z = 0;
        for(int j = 0; j < bodies; j++){
            if(i != j){
                acc[cur_cycle][i] = addVec(acc[cur_cycle][i], 
                                  scaleVec(GravConstant * masses[j] / pow(mod(subV(pos[cur_cycle][i], pos[cur_cycle][j])), 3), 
                                           subV(pos[cur_cycle][j], pos[cur_cycle][i])));
            }
        }
    }

    /* compute positions and velocities */
    /* Ri(t+1) = Ri(t) + Vi(t) + 1/2*Ai(t) */
    /* Vi(t+1) = Vi(t) + Ai(t) */
    if(cur_cycle < cycles - 1) {
        for(int i = 0; i < bodies; i++){
            pos[cur_cycle + 1][i] = addVec(pos[cur_cycle][i], addVec(vel[cur_cycle][i], scaleVec(0.5, acc[cur_cycle][i])));
            vel[cur_cycle + 1][i] = addVec(vel[cur_cycle][i], acc[cur_cycle][i]);
        }
    }
}

void resolve_collision(int cur_cycle){
    /* If two bodies have the same position, their velocities are swapped */
    for(int i = 0; i < bodies - 1; i++)
        for(int j = i + 1; j < bodies; j++){
            if(pos[cur_cycle][i].x == pos[cur_cycle][j].x && pos[cur_cycle][i].y == pos[cur_cycle][j].y && pos[cur_cycle][i].z == pos[cur_cycle][j].z){
                vector temp = vel[cur_cycle][i];
                vel[cur_cycle][i] = vel[cur_cycle][j];
                vel[cur_cycle][j] = temp;
            }
        }
}

void print_variable(int cycle){
    printf("\nCycle %d\n", cycle);
    for(int j = 0; j < bodies; j++){
        printf("Body %d : %lf\t%f\t%lf\t|\t%lf\t%lf\t%lf\n", j, pos[cycle][j].x, pos[cycle][j].y, pos[cycle][j].z, vel[cycle][j].x, vel[cycle][j].y, vel[cycle][j].z);
    }
}

#endif
