<template>
  <el-row>
  <el-col :span="8" v-for="(o, index) in orders" :key="index">
  <el-card class="box-card" shadow="hover">
    <h1 style="margin:0;text-align:center">{{o.number}} {{o.departure}} - {{o.arrival}}</h1>
    <p style="color:#909399"> {{o.date}} ## {{o.startTime}} <br> {{o.class}}座  座位:{{o.seat}}  </p>  
      <el-button style="float: right" size="small" type="danger" round @click="onSubmit(index)">退票</el-button>
    </el-card>
  </el-col>
</el-row>
</template>

<script>
  export default {
    name: 'orders-page',
    methods: {
      open (link) {
        this.$electron.shell.openExternal(link)
      },
      onSubmit (key) {
        console.log(key)
        this.$message({message: '退票成功！', type: 'success'})
      }
    },
    created () {
      let fs = require('fs')
      const { ipcRenderer } = require('electron')
      ipcRenderer.send('get-app-path')
      ipcRenderer.on('got-app-path', (event, path) => {
        fs.readFile(path + '/tickets.json', (err, data) => {
          if (!err) {
            let recs = JSON.parse(data)
            // console.log(recs)
            for (let i of recs) {
              let text = ''
              if (i.seatClass === '1') {
                text = '二等座'
              } else if (i.seatClass === '2') {
                text = '一等座'
              } else {
                text = '商务座'
              }
              this.orders.push({
                number: i.number,
                departure: i.departure,
                arrival: i.arrival,
                date: i.date,
                seat: i.seat[0] + i.seat[1],
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
        orders: []
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
