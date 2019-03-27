<template>
  <el-row>
  <el-col :span="8" v-for="(o, index) in orders" :key="index">
  <el-card class="box-card" shadow="hover">
    <h1 style="margin:0;text-align:center">{{o.number}} {{o.departure}} - {{o.arrival}}</h1>
    <p style="color:#909399"> {{o.date}} {{o.startTime}} {{o.class}}座  座位:{{o.seat}}  </p>  
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
    data () {
      return {
        orders: [{
          number: 'G1',
          departure: '北京西',
          arrival: '上海虹桥',
          class: '一等',
          seat: '3A',
          startTime: '9:00',
          date: '2019-03-27' }, {
          number: 'G5',
          departure: '北京西',
          arrival: '上海虹桥',
          class: '一等',
          seat: '3A',
          startTime: '9:00',
          date: '2019-03-27' }, {
          number: 'G5',
          departure: '北京西',
          arrival: '上海虹桥',
          class: '一等',
          seat: '3A',
          startTime: '9:00',
          date: '2019-03-27' }, {
          number: 'G5',
          departure: '北京西',
          arrival: '上海虹桥',
          class: '一等',
          seat: '3A',
          startTime: '9:00',
          date: '2019-03-27' }
        ]}
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
