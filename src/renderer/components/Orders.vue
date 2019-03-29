<template>
  <el-row>
    <el-col :span="8" v-for="(o, index) in orders" :key="index">
      <el-card class="box-card" shadow="hover">
        <h1 style="margin:0;text-align:center">{{o.number}} {{o.departure}} -> {{o.arrival}}</h1>
        <p style="color:#909399"> {{o.date}}  {{o.startTime}}出发 <br> {{o.class}}座  座位:{{o.seat}}  </p>  
        <el-button style="float: right" size="small" type="danger" round @click="onSubmit(index)">退票</el-button>
      </el-card>
    </el-col>
  </el-row>
</template>

<script>
  let fs = require('fs')
  export default {
    name: 'orders-page',
    methods: {
      onSubmit (key) {
        // console.log(key)
        fs.readFile(this.path + '/tickets.json', (err, data) => {
          if (!err) {
            this.ordersSaved.splice(key, 1)
            this.orders.splice(key, 1)
            // console.log(this.ordersSaved)
            fs.writeFile(this.path + '/tickets.json', JSON.stringify(this.ordersSaved), (err) => {
              if (!err) {
                this.$message({message: '退票成功！', type: 'success'})
              }
            })
          } else {
            this.$message({message: '没有记录！', type: 'warning', showClose: true})
          }
        })
      }
    },
    created () {
      const { ipcRenderer } = require('electron')
      ipcRenderer.send('get-app-path')
      ipcRenderer.on('got-app-path', (event, path) => {
        this.path = path
        fs.readFile(path + '/tickets.json', (err, data) => {
          if (!err) {
            this.ordersSaved = JSON.parse(data)
            // console.log(recs)
            for (let i of this.ordersSaved) {
              let text = ''
              if (i.seatClass === '1') {
                text = '二等'
              } else if (i.seatClass === '2') {
                text = '一等'
              } else {
                text = '商务'
              }
              this.orders.push({
                number: i.number,
                departure: i.departure,
                arrival: i.arrival,
                startTime: i.departureTime,
                date: i.date.slice(0, 10),
                seat: i.seat.value[0] + '车' + i.seat.value[1] + '列' + i.seat.value[2],
                class: text
              })
            }
          } else {
            this.$message({message: '没有记录！', type: 'warning', showClose: true})
          }
        })
      })
    },
    data () {
      return {
        path: '',
        orders: [],
        ordersSaved: []
      }
    }
  }
</script>

<style>
  .input{
    width: 300px;
  }
  .input-card{
    width: 400px;
  }
  .box-card {
    margin: 0.3rem;
    padding-bottom: 1rem
  }
</style>
