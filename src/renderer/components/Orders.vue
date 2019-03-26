<template>
  <el-row>
  <el-col :span="12" v-for="o in orders" :key="o.key">
    <el-card class="box-card input-card" shadow="hover">
    <div slot="header" class="clearfix">
    <span><strong>{{o.number}} {{o.departure}} - {{o.arrival}}</strong></span>
    <el-button style="float: right" size="small"  type="danger" @click="onSubmit()">退票</el-button>
    </div>
  <h3> {{o.class}}座  座位:{{o.seat}} <br> {{o.startTime}} - {{o.endTime}}</h3>  
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
      onSubmit () {
        alert('submit!')
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
          endTime: '12:00' }, {
          number: 'G5',
          departure: '北京西',
          arrival: '上海虹桥',
          class: '一等',
          seat: '3A',
          startTime: '9:00',
          endTime: '12:00' }
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
</style>
